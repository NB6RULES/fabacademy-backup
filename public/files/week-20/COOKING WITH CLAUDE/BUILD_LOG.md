# Smart Tool Box — Cloud Build Log

A running log of the Firebase + app + firmware cloud integration, kept as we go.
Newest work is appended at the bottom. Secrets (the device password) are **never** written
here — they live only in `SmartToolBox/cloud_secrets.h`, which is git-ignored.

---

## The goal

Take the already-working Smart Tool Box firmware (XIAO ESP32-C6: 19-node daisy-chain of
limit/Hall switches, 299-LED rainbow, RC522 RFID unlock, 3 solenoid drawer locks) and put it
online:

```
ESP32-C6  ──HTTPS──>  Firestore  <──live──  Flutter app (phone)
  writes tool presence,             reads tool state, event log,
  events, heartbeat                 device status; admin manages users
```

Single-admin / single-device security model — roles are decided by the signed-in email.

---

## Components & their state

| Piece | Where | Status |
|---|---|---|
| Firmware (sensors/LED/RFID/solenoid) | `SmartToolBox/SmartToolBox.ino` | existed (Phase 1) |
| WiFi join + provisioning portal | `SmartToolBox/wifi_manager.*` | existed |
| **Cloud client (ESP → Firestore)** | `SmartToolBox/firestore_client.*` | **built this session** |
| Firestore security rules | `cloud/firestore.rules` | deployed |
| Firestore schema (reference) | `cloud/schema.md` | existed |
| Flutter app | `smarttoolbox_app/` | wired to live project |

**Firebase project:** `smart-tool-box-2efc9`
- Web API key: `REDACTED_FIREBASE_WEB_API_KEY` (client config, not a secret)
- Admin role: `nadecbiju6@gmail.com` (the Gmail you log into the app with)
- Device role: `device@smarttoolbox.local` (the ESP's login; password in `cloud_secrets.h`)

---

## Firestore data model (what the ESP writes, what the app reads)

- `devices/main-box` — heartbeat: `online`, `lastSeen`, `fwVersion` (admin owns `allowlistVersion`)
- `tools/tool_NN` — live slot state: `present`, `nodeId`, `drawer`, `updatedAt`
  (ESP owns these; **admin owns `name`** so the two never collide). `NN` = zero-padded node id.
- `events/{autoId}` — append-only log: `taken` / `returned` / `unlock` / `drawer_open` / `drawer_close`
- `users/{uid}` — RFID users + allowed drawers (admin writes, device reads — not used by ESP yet)

**Drawer map (firmware):** nodes 1–9 → drawer 1, nodes 11–17 → drawer 2. Nodes 10/18/19 are
the Hall drawer sensors, not tools.

---

## Timeline

### 1. Firebase project + auth (you, in the console)
- Created project `smart-tool-box-2efc9`, grabbed the web config.
- Authentication → Email/Password → added two users:
  - `nadecbiju6@gmail.com` (admin)
  - `device@smarttoolbox.local` (device)

### 2. Security rules — deployed
- Filled the two placeholders in `cloud/firestore.rules` with the real emails.
- Created `cloud/.firebaserc` (`default` → `smart-tool-box-2efc9`) so we skip interactive
  `firebase use --add`.
- `firebase deploy --only firestore:rules` → compiled clean, released to `cloud.firestore`.
- Result: device can patch `tools`/`devices` + create `events` + read `users`; only admin can
  manage `users`; everything else denied.

### 3. Flutter app wired to the live project
- `dart pub global activate flutterfire_cli` (1.4.0).
- `flutterfire configure --project=smart-tool-box-2efc9 --platforms=android,ios --yes`
  - registered real Android (`com.nadecbiju.smarttoolbox_app`) + iOS apps,
  - regenerated `lib/firebase_options.dart` with real per-platform keys,
  - dropped `android/app/google-services.json`.
- `flutter pub get` ✓ then `flutter analyze` → **No issues found**.

### 4. Phase 2 — ESP → Firestore client (built this session)
New files in `SmartToolBox/`:
- `firestore_client.h` / `.cpp` — the cloud client.
- `cloud_secrets.h` — real creds (**git-ignored**).
- `cloud_secrets.example.h` — committable template.
- `.gitignore` — ignores `cloud_secrets.h`.

Edits to `SmartToolBox.ino`:
- `#include "firestore_client.h"`.
- Added `drawerForToolNode()` helper.
- `parseChain()` now enqueues tool presence (every change + boot sync) and drawer open/close.
- `serviceRFID()` builds the uppercase colon-hex tag and enqueues an `unlock` event.
- `setup()` calls `Cloud::begin()` after WiFi comes up.

**Compile check (real target):**
`arduino-cli compile --fqbn esp32:esp32:XIAO_ESP32C6 ./SmartToolBox` → **success**.
- Flash: 1,193,822 / 1,310,720 bytes = **91%** (fits, but tight — see watch-item below).
- RAM (globals): 44,672 / 327,680 bytes = 13%.
- Toolchain: arduino-cli 1.4.1, esp32 core 3.3.7, ArduinoJson 7.4.3, NeoPixel 1.15.4, MFRC522 1.4.12.

---

## Key decisions & why

- **Cloud I/O on its own FreeRTOS task, not in `loop()`.** The whole sketch is built around
  "the rainbow never stutters — no blocking `delay()` in `loop()`." An HTTPS write blocks
  200–800 ms, which would freeze the LEDs. So the main loop only drops tiny structs on a
  FreeRTOS queue (`xQueueSend`, 0 timeout → never blocks, drops if full); the background task
  owns sign-in, token refresh, the queue drain, and the heartbeat.

- **Lightweight REST, no heavy Firebase library.** `WiFiClientSecure` + `HTTPClient` +
  `ArduinoJson` (already a dependency) talking to the Firestore + Identity Toolkit REST APIs.
  Avoids the bulk/quirks of full Firebase-ESP client libraries and matches the minimal style
  of the existing code.

- **Device (NTP) timestamps, not server transforms.** Server timestamps need the Firestore
  `:commit` endpoint with field transforms (more complex JSON). Instead the ESP syncs NTP and
  writes RFC3339 `timestampValue`s, keeping each write a single HTTP call. The app reads them
  as real `Timestamp`s either way; tradeoff is ~seconds of clock skew.

- **ESP owns `present/nodeId/drawer/updatedAt`; admin owns `name`.** Tool PATCHes use an
  explicit `updateMask` that never includes `name`, so naming a tool in the app survives the
  next sensor update. Because the doc always carries `drawer`, it shows up in the app's
  `orderBy('drawer')` list immediately (name fills in when the admin sets it).

- **Boot sync vs. history.** On the first chain poll the ESP pushes current presence as
  state-only (`logEvent=false`) so the app reflects reality at power-on without inventing a
  pile of fake taken/returned events.

- **Secrets out of git.** The device password would otherwise be committed to a public FAB
  repo. `cloud_secrets.h` is git-ignored; a clone copies `cloud_secrets.example.h` and fills
  it in. (Firebase web/mobile API keys are *not* secrets — they're protected by the rules — so
  `firebase_options.dart`/`google-services.json` staying committed is fine.)

- **`setInsecure()` TLS.** Skips cert pinning — pragmatic for a project. Could pin the Google
  root CA later if we want.

---

## Open items / next steps

- [ ] Confirm the `device@smarttoolbox.local` account is actually created (Add user clicked).
- [x] Compile the firmware — **done, compiles clean for XIAO ESP32-C6.**
- [ ] Flash to the XIAO — board is at the lab, so this waits until Nadec is back.
- [ ] **Watch flash usage (91%).** If we add features and it overflows, switch the partition
      scheme to "Huge APP (3MB No OTA)" in board options (the C6 has 4MB flash).
- [ ] Seed/observe `tools/tool_NN` docs appearing; set tool `name`s from the app's admin panel.
- [ ] Smoke-test the app against live Firestore (log in as admin, watch state update).
- [ ] Later: RFID → user mapping (who took what) + allow-list enforcement on the device,
      driven by `devices/main-box.allowlistVersion`.
- [ ] Later: move device creds from `cloud_secrets.h` to app-based provisioning (like WiFi),
      so nothing sensitive is compiled in at all.

---

## Change history (running)

- **2026-06-09** — Started this build log at Nadec's request.
- **2026-06-09** — Deployed rules; wired app via flutterfire; built Phase 2 cloud client
  (`firestore_client.*`) + `cloud_secrets` files + `.gitignore`; hooked enqueues into
  `SmartToolBox.ino`. App passes `flutter analyze`.
- **2026-06-09** — Compiled the firmware for the XIAO ESP32-C6: **success at 91% flash / 13% RAM.**
  Phase 2 cloud code verified at the compiler level on the real target. Flashing waits for the board.
