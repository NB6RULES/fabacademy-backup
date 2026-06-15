#include "firestore_client.h"
#include "cloud_secrets.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

// =====================================================================================
//  Endpoints
// =====================================================================================
#define SIGNIN_URL  "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" FB_API_KEY
#define REFRESH_URL "https://securetoken.googleapis.com/v1/token?key=" FB_API_KEY
#define FS_BASE     "https://firestore.googleapis.com/v1/projects/" FB_PROJECT_ID "/databases/(default)/documents"

// =====================================================================================
//  Tunables
// =====================================================================================
static const uint32_t HEARTBEAT_MS   = 30000;   // device heartbeat cadence
static const uint32_t TOKEN_SKEW_MS  = 300000;  // refresh 5 min before expiry
static const uint32_t SIGNIN_RETRY_MS= 10000;   // wait between failed sign-in attempts
static const uint16_t QUEUE_LEN      = 24;      // pending messages from the main loop
static const uint16_t TASK_STACK     = 10240;   // TLS needs a roomy stack

// =====================================================================================
//  Queue message (kept tiny — copied by value into the FreeRTOS queue)
// =====================================================================================
enum MsgKind : uint8_t { MSG_TOOL, MSG_DRAWER, MSG_UNLOCK };

struct CloudMsg {
  uint8_t kind;
  uint8_t nodeId;
  uint8_t drawer;
  bool    state;      // tool: present?   drawer: open?
  bool    logEvent;   // tool: also append taken/returned
  char    rfid[24];   // unlock: raw tag, colon-hex
};

// =====================================================================================
//  Module state (touched only by the cloud task, except the queue handle)
// =====================================================================================
namespace {
  QueueHandle_t     q          = nullptr;
  WiFiClientSecure  secure;                 // reused across requests
  String            idToken    = "";
  String            refreshTok = "";
  uint32_t          tokenGoodUntil = 0;     // millis() deadline to refresh by
  volatile bool     ready      = false;

  // ---- helpers ---------------------------------------------------------------------

  String docIdForNode(uint8_t n) {
    char b[12];
    snprintf(b, sizeof(b), "tool_%02u", n);
    return String(b);
  }

  // RFC3339 UTC timestamp from the (NTP-synced) clock. Firestore stores it as a real
  // Timestamp; we use device time (NTP) rather than a server transform to keep each
  // write a single HTTP call.
  String isoNow() {
    time_t now = time(nullptr);
    struct tm t;
    gmtime_r(&now, &t);
    char buf[24];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &t);
    return String(buf);
  }

  bool timeSynced() { return time(nullptr) > 1700000000; }  // ~2023-11 onward

  // One HTTPS round-trip. Returns the HTTP status code (<0 on transport error).
  int httpsReq(const char* method, const String& url, const String& body,
               const char* contentType, const String& bearer, String& out) {
    HTTPClient http;
    if (!http.begin(secure, url)) return -1;
    http.setTimeout(8000);
    if (contentType)        http.addHeader("Content-Type", contentType);
    if (bearer.length())    http.addHeader("Authorization", "Bearer " + bearer);
    int code = http.sendRequest(method, (uint8_t*)body.c_str(), body.length());
    out = (code > 0) ? http.getString() : "";
    http.end();
    return code;
  }

  // ---- auth ------------------------------------------------------------------------

  bool signIn() {
    JsonDocument req;
    req["email"]             = FB_DEVICE_EMAIL;
    req["password"]          = FB_DEVICE_PASSWORD;
    req["returnSecureToken"] = true;
    String body; serializeJson(req, body);

    String resp;
    int code = httpsReq("POST", SIGNIN_URL, body, "application/json", "", resp);
    if (code != 200) {
      Serial.printf("[cloud] sign-in failed (HTTP %d): %s\n", code, resp.c_str());
      return false;
    }
    JsonDocument r;
    if (deserializeJson(r, resp)) return false;
    idToken    = r["idToken"].as<String>();
    refreshTok = r["refreshToken"].as<String>();
    uint32_t ttl = r["expiresIn"].as<String>().toInt() * 1000UL;   // seconds -> ms
    tokenGoodUntil = millis() + (ttl > TOKEN_SKEW_MS ? ttl - TOKEN_SKEW_MS : ttl / 2);
    Serial.println(F("[cloud] signed in as device account"));
    return idToken.length() > 0;
  }

  bool refreshToken() {
    String body = "grant_type=refresh_token&refresh_token=" + refreshTok;
    String resp;
    int code = httpsReq("POST", REFRESH_URL, body,
                        "application/x-www-form-urlencoded", "", resp);
    if (code != 200) {
      Serial.printf("[cloud] token refresh failed (HTTP %d)\n", code);
      return false;
    }
    JsonDocument r;
    if (deserializeJson(r, resp)) return false;
    idToken    = r["id_token"].as<String>();
    refreshTok = r["refresh_token"].as<String>();
    uint32_t ttl = r["expires_in"].as<String>().toInt() * 1000UL;
    tokenGoodUntil = millis() + (ttl > TOKEN_SKEW_MS ? ttl - TOKEN_SKEW_MS : ttl / 2);
    return idToken.length() > 0;
  }

  // Make sure we hold a usable token; (re)sign-in or refresh as needed.
  bool ensureAuth() {
    if (idToken.isEmpty())                         return signIn();
    if ((int32_t)(millis() - tokenGoodUntil) >= 0) return refreshToken() || signIn();
    return true;
  }

  // ---- Firestore writes ------------------------------------------------------------

  // PATCH a doc with an explicit field mask. Retries once after re-auth on a 401.
  bool patchDoc(const String& path, const String& fields, const String& mask) {
    String url = String(FS_BASE) + "/" + path + "?" + mask;
    String resp;
    int code = httpsReq("PATCH", url, fields, "application/json", idToken, resp);
    if (code == 401 && ensureAuth())
      code = httpsReq("PATCH", url, fields, "application/json", idToken, resp);
    if (code != 200) {
      Serial.printf("[cloud] PATCH %s -> HTTP %d\n", path.c_str(), code);
      return false;
    }
    return true;
  }

  // POST a new auto-id doc into a collection. Retries once after re-auth on a 401.
  bool createDoc(const String& collection, const String& fields) {
    String url = String(FS_BASE) + "/" + collection;
    String resp;
    int code = httpsReq("POST", url, fields, "application/json", idToken, resp);
    if (code == 401 && ensureAuth())
      code = httpsReq("POST", url, fields, "application/json", idToken, resp);
    if (code != 200) {
      Serial.printf("[cloud] POST %s -> HTTP %d\n", collection.c_str(), code);
      return false;
    }
    return true;
  }

  // ---- typed-value body builders (Firestore REST uses tagged JSON) -----------------

  void patchTool(uint8_t nodeId, uint8_t drawer, bool present) {
    JsonDocument d;
    JsonObject f = d["fields"].to<JsonObject>();
    f["present"]["booleanValue"]   = present;
    f["nodeId"]["integerValue"]    = String(nodeId);
    f["drawer"]["integerValue"]    = String(drawer);
    f["updatedAt"]["timestampValue"] = isoNow();
    String body; serializeJson(d, body);
    patchDoc("tools/" + docIdForNode(nodeId), body,
             "updateMask.fieldPaths=present&updateMask.fieldPaths=nodeId"
             "&updateMask.fieldPaths=drawer&updateMask.fieldPaths=updatedAt");
  }

  void postToolEvent(const char* type, uint8_t nodeId, uint8_t drawer) {
    JsonDocument d;
    JsonObject f = d["fields"].to<JsonObject>();
    f["type"]["stringValue"]    = type;
    f["toolId"]["stringValue"]  = docIdForNode(nodeId);
    f["nodeId"]["integerValue"] = String(nodeId);
    f["drawer"]["integerValue"] = String(drawer);
    f["ts"]["timestampValue"]   = isoNow();
    String body; serializeJson(d, body);
    createDoc("events", body);
  }

  void postDrawerEvent(const char* type, uint8_t drawer, uint8_t nodeId) {
    JsonDocument d;
    JsonObject f = d["fields"].to<JsonObject>();
    f["type"]["stringValue"]    = type;
    f["drawer"]["integerValue"] = String(drawer);
    f["nodeId"]["integerValue"] = String(nodeId);
    f["ts"]["timestampValue"]   = isoNow();
    String body; serializeJson(d, body);
    createDoc("events", body);
  }

  void postUnlockEvent(const char* rfid) {
    JsonDocument d;
    JsonObject f = d["fields"].to<JsonObject>();
    f["type"]["stringValue"]    = "unlock";
    f["rfidUid"]["stringValue"] = rfid;
    f["ts"]["timestampValue"]   = isoNow();
    String body; serializeJson(d, body);
    createDoc("events", body);
  }

  void sendHeartbeat() {
    JsonDocument d;
    JsonObject f = d["fields"].to<JsonObject>();
    f["name"]["stringValue"]      = FB_DEVICE_ID;
    f["online"]["booleanValue"]   = true;
    f["lastSeen"]["timestampValue"] = isoNow();
    f["fwVersion"]["stringValue"] = FB_FW_VERSION;
    String body; serializeJson(d, body);
    patchDoc(String("devices/") + FB_DEVICE_ID, body,
             "updateMask.fieldPaths=name&updateMask.fieldPaths=online"
             "&updateMask.fieldPaths=lastSeen&updateMask.fieldPaths=fwVersion");
  }

  void handleMsg(const CloudMsg& m) {
    switch (m.kind) {
      case MSG_TOOL:
        patchTool(m.nodeId, m.drawer, m.state);
        if (m.logEvent) postToolEvent(m.state ? "returned" : "taken", m.nodeId, m.drawer);
        break;
      case MSG_DRAWER:
        postDrawerEvent(m.state ? "drawer_open" : "drawer_close", m.drawer, m.nodeId);
        break;
      case MSG_UNLOCK:
        postUnlockEvent(m.rfid);
        break;
    }
  }

  // ---- the task --------------------------------------------------------------------
  void cloudTask(void*) {
    secure.setInsecure();                       // skip cert pinning (project-grade)

    for (;;) {
      // (1) need WiFi before anything cloud-y
      if (WiFi.status() != WL_CONNECTED) {
        ready = false;
        vTaskDelay(pdMS_TO_TICKS(500));
        continue;
      }

      // (2) NTP clock for valid timestamps
      if (!timeSynced()) {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
        uint32_t t0 = millis();
        while (!timeSynced() && millis() - t0 < 8000) vTaskDelay(pdMS_TO_TICKS(200));
        if (!timeSynced()) { vTaskDelay(pdMS_TO_TICKS(1000)); continue; }
      }

      // (3) authenticated session
      if (!ensureAuth()) {
        ready = false;
        vTaskDelay(pdMS_TO_TICKS(SIGNIN_RETRY_MS));
        continue;
      }
      ready = true;

      // (4) serve the queue + heartbeat. Block up to the next heartbeat for a message.
      static uint32_t lastBeat = 0;
      if (lastBeat == 0) { sendHeartbeat(); lastBeat = millis(); }

      uint32_t since = millis() - lastBeat;
      uint32_t wait  = (since >= HEARTBEAT_MS) ? 0 : (HEARTBEAT_MS - since);

      CloudMsg m;
      if (q && xQueueReceive(q, &m, pdMS_TO_TICKS(wait)) == pdTRUE) {
        handleMsg(m);
      }
      if (millis() - lastBeat >= HEARTBEAT_MS) {
        sendHeartbeat();
        lastBeat = millis();
      }
    }
  }

  // ---- enqueue (called from the main loop) -----------------------------------------
  void post(const CloudMsg& m) {
    if (q) xQueueSend(q, &m, 0);   // never block the main loop; drop if the queue is full
  }
}

// =====================================================================================
//  Public API
// =====================================================================================
namespace Cloud {

  void begin() {
    q = xQueueCreate(QUEUE_LEN, sizeof(CloudMsg));
    xTaskCreate(cloudTask, "cloud", TASK_STACK, nullptr, 1, nullptr);
    Serial.println(F("[cloud] background task started"));
  }

  bool isReady() { return ready; }

  void reportTool(uint8_t nodeId, uint8_t drawer, bool present, bool logEvent) {
    CloudMsg m{};
    m.kind = MSG_TOOL; m.nodeId = nodeId; m.drawer = drawer;
    m.state = present;  m.logEvent = logEvent;
    post(m);
  }

  void reportDrawer(uint8_t drawer, uint8_t nodeId, bool open) {
    CloudMsg m{};
    m.kind = MSG_DRAWER; m.drawer = drawer; m.nodeId = nodeId; m.state = open;
    post(m);
  }

  void reportUnlock(const String& rfidUid) {
    CloudMsg m{};
    m.kind = MSG_UNLOCK;
    strncpy(m.rfid, rfidUid.c_str(), sizeof(m.rfid) - 1);
    post(m);
  }
}
