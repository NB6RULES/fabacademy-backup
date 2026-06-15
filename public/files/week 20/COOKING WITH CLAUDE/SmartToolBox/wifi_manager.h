// WiFi manager for the Smart Tool Box.
//
// On begin(): loads the list of saved networks from NVS, scans, and connects to the
// strongest saved network in range. If none connect, it starts its own access point
// "SmartToolBox-XXXX" so the phone app (or a browser) can set things up.
//
// A small web server runs in BOTH modes (AP and connected) exposing a JSON API that the
// portal page AND the Flutter app share:
//
//   GET  /          -> the management page (scan list + saved list, all client-side JS)
//   GET  /scan      -> {"networks":[{"ssid","rssi","secure"}, ...]}   (live scan)
//   GET  /saved     -> {"saved":["ssidA","ssidB", ...]}
//   POST /wifi       (ssid, pass) -> add or update a saved network
//   POST /forget     (ssid)       -> remove a saved network
//   POST /connect                 -> reboot and connect using the saved list
//
// loop() services the web server.
#pragma once
#include <Arduino.h>

namespace WifiManager {
  void   begin();            // load saved nets, connect, or fall back to AP
  void   loop();             // service the web server
  bool   isOnline();         // station connected to a real network
  bool   isProvisioning();   // currently running the setup AP
  String ip();               // current IP (AP or station)
}
