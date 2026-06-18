// Firestore client for the Smart Tool Box  (Phase 2: ESP -> Firestore).
//
// Runs ALL cloud I/O on its own FreeRTOS task so the main loop never blocks — an HTTPS
// write takes 200-800 ms and would freeze the rainbow if done inline. The main loop only
// drops tiny messages on a queue (the report* calls below); the task signs in with the
// device account, refreshes the token, and pushes state/events to Firestore.
//
// Mirrors cloud/schema.md exactly:
//   tools/tool_NN   present + nodeId + drawer + updatedAt   (admin owns 'name')
//   events/{auto}   taken | returned | unlock | drawer_open | drawer_close
//   devices/main-box  online + lastSeen + fwVersion         (heartbeat)
//
// All credentials come from cloud_secrets.h (git-ignored).
#pragma once
#include <Arduino.h>

namespace Cloud {
  // Start the background cloud task. Call once in setup() AFTER WifiManager::begin().
  void begin();

  // True once the device account is signed in and the token is valid.
  bool isReady();

  // ---- enqueue from the main loop (non-blocking, safe to call every poll) ----

  // Live tool presence for a sensor node. logEvent=true also appends a taken/returned
  // event; pass false for the initial boot sync (state only, no spurious history).
  void reportTool(uint8_t nodeId, uint8_t drawer, bool present, bool logEvent);

  // Drawer hall sensor changed. Appends a drawer_open / drawer_close event.
  void reportDrawer(uint8_t drawer, uint8_t nodeId, bool open);

  // RFID tag tapped -> box unlocked. Appends an unlock event with the raw tag.
  void reportUnlock(const String& rfidUid);
}
