#include "wifi_manager.h"
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ArduinoJson.h>

namespace {
  constexpr uint8_t MAX_NETS = 8;

  struct Net { String ssid; String pass; };
  Net     saved[MAX_NETS];
  uint8_t savedCount   = 0;

  Preferences prefs;
  WebServer   server(80);
  bool        apMode        = false;
  bool        serverStarted = false;
  String      apName;

  // ---- the management page: a tiny client-side app that drives the JSON API ----
  const char PAGE[] PROGMEM = R"HTML(<!doctype html><html><head>
<meta name='viewport' content='width=device-width,initial-scale=1'>
<title>Smart Tool Box WiFi</title><style>
body{font-family:sans-serif;max-width:440px;margin:20px auto;padding:0 12px}
h3{margin:18px 0 6px}button{padding:7px 11px;margin:0 0 0 4px;cursor:pointer}
input{width:100%;padding:9px;box-sizing:border-box;margin:3px 0}
.row{display:flex;justify-content:space-between;align-items:center;border-bottom:1px solid #eee;padding:7px 0}
.muted{color:#888;font-size:12px}</style></head><body>
<h2>Smart Tool Box &mdash; WiFi</h2>
<h3>Available networks <button onclick='scan()'>&#x21bb;</button></h3>
<div id='scanlist' class='muted'>scanning&hellip;</div>
<h3>Add / update password</h3>
<input id='ssid' placeholder='SSID'>
<input id='pass' type='password' placeholder='password (blank = open)'>
<button onclick='save()'>Save</button>
<button onclick='apply()'>Save &amp; connect (reboot)</button>
<h3>Saved networks</h3>
<div id='savedlist' class='muted'>&hellip;</div>
<script>
const ssid=document.getElementById('ssid'),pass=document.getElementById('pass'),
sl=document.getElementById('scanlist'),vl=document.getElementById('savedlist');
function api(p,b){return fetch(p,{method:b?'POST':'GET',
 headers:b?{'Content-Type':'application/x-www-form-urlencoded'}:{},body:b||undefined}).then(r=>r.json())}
function row(label,sub){const d=document.createElement('div');d.className='row';
 const s=document.createElement('span');s.textContent=label;
 if(sub){const m=document.createElement('span');m.className='muted';m.textContent=' '+sub;s.appendChild(m)}
 d.appendChild(s);return d}
function btn(t,fn){const b=document.createElement('button');b.textContent=t;b.onclick=fn;return b}
function scan(){sl.textContent='scanning…';api('/scan').then(d=>{sl.innerHTML='';
 (d.networks||[]).forEach(n=>{const r=row(n.ssid,n.rssi+'dBm '+(n.secure?'\u{1F512}':''));
  r.appendChild(btn('use',()=>{ssid.value=n.ssid;pass.value='';pass.focus()}));sl.appendChild(r)});
 if(!sl.children.length)sl.textContent='none found'}).catch(()=>sl.textContent='scan failed')}
function loadSaved(){api('/saved').then(d=>{vl.innerHTML='';
 (d.saved||[]).forEach(s=>{const r=row(s,'');
  r.appendChild(btn('edit',()=>{ssid.value=s;pass.value='';pass.focus()}));
  r.appendChild(btn('forget',()=>api('/forget',new URLSearchParams({ssid:s})).then(loadSaved)));
  vl.appendChild(r)});if(!vl.children.length)vl.textContent='none saved'})}
function save(){if(!ssid.value){alert('enter SSID');return}
 api('/wifi',new URLSearchParams({ssid:ssid.value,pass:pass.value})).then(()=>{pass.value='';loadSaved()})}
function apply(){const go=()=>{if(confirm('Reboot to connect?'))
  api('/connect','x').then(()=>alert('Rebooting — reconnect to your WiFi'))};
 if(ssid.value)api('/wifi',new URLSearchParams({ssid:ssid.value,pass:pass.value})).then(go);else go()}
scan();loadSaved();
</script></body></html>)HTML";

  // ---------------------------------------------------------------- NVS list ----
  void loadSaved() {
    prefs.begin("wifi", true);
    savedCount = prefs.getUChar("count", 0);
    if (savedCount > MAX_NETS) savedCount = MAX_NETS;
    char k[8];
    for (uint8_t i = 0; i < savedCount; i++) {
      snprintf(k, sizeof(k), "ssid%u", i); saved[i].ssid = prefs.getString(k, "");
      snprintf(k, sizeof(k), "pass%u", i); saved[i].pass = prefs.getString(k, "");
    }
    prefs.end();
  }

  void persistSaved() {
    prefs.begin("wifi", false);
    prefs.putUChar("count", savedCount);
    char k[8];
    for (uint8_t i = 0; i < savedCount; i++) {
      snprintf(k, sizeof(k), "ssid%u", i); prefs.putString(k, saved[i].ssid);
      snprintf(k, sizeof(k), "pass%u", i); prefs.putString(k, saved[i].pass);
    }
    prefs.end();
  }

  void addOrUpdate(const String& ssid, const String& pass) {
    for (uint8_t i = 0; i < savedCount; i++) {
      if (saved[i].ssid == ssid) { saved[i].pass = pass; persistSaved(); return; }
    }
    if (savedCount < MAX_NETS) {
      saved[savedCount].ssid = ssid;
      saved[savedCount].pass = pass;
      savedCount++;
      persistSaved();
    }
  }

  void forget(const String& ssid) {
    for (uint8_t i = 0; i < savedCount; i++) {
      if (saved[i].ssid == ssid) {
        for (uint8_t j = i; j + 1 < savedCount; j++) saved[j] = saved[j + 1];
        savedCount--;
        persistSaved();
        return;
      }
    }
  }

  // ---------------------------------------------------------------- handlers ----
  void handleRoot() { server.send_P(200, "text/html", PAGE); }

  void handleScan() {
    int n = WiFi.scanNetworks();
    JsonDocument doc;
    JsonArray arr = doc["networks"].to<JsonArray>();
    for (int i = 0; i < n; i++) {
      JsonObject o = arr.add<JsonObject>();
      o["ssid"]   = WiFi.SSID(i);
      o["rssi"]   = WiFi.RSSI(i);
      o["secure"] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
    }
    WiFi.scanDelete();
    String out; serializeJson(doc, out);
    server.send(200, "application/json", out);
  }

  void handleSavedList() {
    JsonDocument doc;
    JsonArray arr = doc["saved"].to<JsonArray>();
    for (uint8_t i = 0; i < savedCount; i++) arr.add(saved[i].ssid);
    String out; serializeJson(doc, out);
    server.send(200, "application/json", out);
  }

  void handleSaveWifi() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    if (ssid.isEmpty()) {
      server.send(400, "application/json", "{\"ok\":false,\"err\":\"ssid required\"}");
      return;
    }
    addOrUpdate(ssid, pass);
    Serial.printf("[wifi] saved network '%s' (%u total)\n", ssid.c_str(), savedCount);
    server.send(200, "application/json", "{\"ok\":true}");
  }

  void handleForget() {
    String ssid = server.arg("ssid");
    forget(ssid);
    Serial.printf("[wifi] forgot network '%s' (%u total)\n", ssid.c_str(), savedCount);
    server.send(200, "application/json", "{\"ok\":true}");
  }

  void handleConnect() {
    server.send(200, "application/json", "{\"ok\":true,\"msg\":\"rebooting\"}");
    delay(400);
    ESP.restart();
  }

  void startServer() {
    if (serverStarted) return;
    server.on("/",        HTTP_GET,  handleRoot);
    server.on("/scan",    HTTP_GET,  handleScan);
    server.on("/saved",   HTTP_GET,  handleSavedList);
    server.on("/wifi",    HTTP_POST, handleSaveWifi);
    server.on("/forget",  HTTP_POST, handleForget);
    server.on("/connect", HTTP_POST, handleConnect);
    server.begin();
    serverStarted = true;
  }

  void startAP() {
    apMode = true;
    WiFi.mode(WIFI_AP_STA);                 // AP for the portal + STA so /scan works
    uint8_t mac[6];
    WiFi.softAPmacAddress(mac);
    char suffix[5];
    snprintf(suffix, sizeof(suffix), "%02X%02X", mac[4], mac[5]);
    apName = String("SmartToolBox-") + suffix;
    WiFi.softAP(apName.c_str());
    Serial.printf("[wifi] no saved network in range -> AP '%s' @ %s (http://192.168.4.1)\n",
                  apName.c_str(), WiFi.softAPIP().toString().c_str());
  }

  // Scan, then connect to the strongest saved network that is actually in range.
  bool connectToBest() {
    WiFi.mode(WIFI_STA);
    int n = WiFi.scanNetworks();
    int  bestSaved = -1, bestRssi = -1000;
    for (uint8_t s = 0; s < savedCount; s++) {
      for (int i = 0; i < n; i++) {
        if (WiFi.SSID(i) == saved[s].ssid && WiFi.RSSI(i) > bestRssi) {
          bestRssi = WiFi.RSSI(i);
          bestSaved = s;
        }
      }
    }
    WiFi.scanDelete();
    if (bestSaved < 0) return false;

    Serial.printf("[wifi] connecting to '%s' (%d dBm) ...\n",
                  saved[bestSaved].ssid.c_str(), bestRssi);
    WiFi.begin(saved[bestSaved].ssid.c_str(), saved[bestSaved].pass.c_str());
    uint32_t t0 = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t0 < 12000) delay(200);
    return WiFi.status() == WL_CONNECTED;
  }
}

namespace WifiManager {

  void begin() {
    loadSaved();
    if (savedCount > 0 && connectToBest()) {
      WiFi.setAutoReconnect(true);
      apMode = false;
      Serial.printf("[wifi] connected, IP %s  (%u saved networks)\n",
                    WiFi.localIP().toString().c_str(), savedCount);
    } else {
      startAP();
    }
    startServer();                          // management API available in both modes
  }

  void loop()           { if (serverStarted) server.handleClient(); }
  bool isOnline()       { return WiFi.status() == WL_CONNECTED; }
  bool isProvisioning() { return apMode; }
  String ip()           { return apMode ? WiFi.softAPIP().toString()
                                        : WiFi.localIP().toString(); }
}
