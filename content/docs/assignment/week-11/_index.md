+++
title = "Week 11 - Networking and Communications"
weight = 111
bookCollapseSection = true
+++

# Week 11 - Networking and Communications

Week 11 was all about networking and communications — actually getting devices to talk to each other, not just in theory but in a way where something physical happens at the other end.

The individual assignment was to design, build, and connect wired or wireless nodes with network or bus addresses and local input/output. I took that as a chance to build something I'd actually use: a wireless QWERTY keyboard system where you type on a physical device and the text appears on your PC.

This week built directly on the board I made in Week 8. The custom PCB already has 6 push buttons and an OLED header onboard, so I didn't need to wire anything extra on the ESP32 side. The other node is a bare Raspberry Pi Pico W connected to my PC via USB — no custom board, just the chip itself.

---

## Group Assignment
- Send a message between two projects

## Individual Assignment
- Design, build, and connect wired or wireless node(s) with network or bus addresses and local input &/or output device(s)

Extra Credit Goals:
- Try multiple communication protocols (I2C, SPI, UART, Wi-Fi, Bluetooth, etc.)
- Implement a network of more than two nodes

---

## What I Learned

- WiFi AP mode vs STA mode — and why AP made way more sense here (portability, no router dependency, the two devices just form their own network)
- UDP vs TCP for short bursts: no handshake, no connection state, lower overhead. If a packet drops, you just hit SEND again. Simple.
- The Pico W can act as a USB HID keyboard to your PC with zero driver setup — the OS literally just sees it as a keyboard
- The ESP32-C6 can't do USB HID at all. It only has USB Serial/JTAG hardware, no OTG. This is why the Pico W exists in this setup.
- Debounce and multi-gesture detection (single tap, double tap, long press) without any `delay()` — all done with `millis()` timers
- Serving HTML from an ESP32 with no filesystem — you store the page in `PROGMEM` so it lives in flash instead of eating your RAM
- I2C at a practical level: two wires (SDA + SCL), main picks the secondary by address, the library handles all the framing. You just call `display.display()`.

---

## Software Used
- Arduino IDE — firmware for both boards
- Serial Monitor — debugging WiFi connection and UDP packet flow on the Pico W
- Browser — testing the web UI served by the ESP32-C6

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on networking and communications |
| THU | Planned the two-node architecture, decided on WiFi UDP + USB HID approach |
| FRI | Wrote and tested ESP32-C6 firmware — WiFi AP, web server, OLED keyboard UI |
| SAT | Wrote and tested Pico W firmware — WiFi client, UDP listener, USB HID output |
| SUN | Integration testing — full end-to-end text from OLED keyboard to PC |
| MON | Web UI polish, documentation writeup |
| TUE | Regional review |

---

# Wireless QWERTY Keyboard System
### XIAO ESP32-C6 (custom Week 8 PCB) + Raspberry Pi Pico W

A two-device wireless text input system. You type on a physical QWERTY keyboard rendered on an OLED display (or via a web browser), and the text gets wirelessly transmitted to a Raspberry Pi Pico W which types it on your PC as if it were a real USB keyboard.

---

## How it works — big picture

![bd-1](../../../images/week-11/bd-1.jpg)

---

## Hardware

### Device 1 — Custom Week 8 PCB (XIAO ESP32-C6)

This is the custom PCB I designed in Week 6 and milled/soldered in Week 8. The XIAO ESP32-C6 is soldered directly onto it, and all 6 buttons plus the I2C header are already wired up — no breadboarding needed on this side.

| Component | Role |
|-----------|------|
| Seeed XIAO ESP32-C6 | Main MCU — runs WiFi AP, web server, OLED UI |
| SSD1306 OLED 128×64 | Connected via the I2C header (J1) on the PCB |
| 6× push buttons (onboard) | Navigation (UP/DOWN/LEFT/RIGHT/SPACE/SEND) |

#### OLED wiring (I2C header on PCB)

The OLED plugs into the 4-pin I2C header (J1) already broken out on the Week 8 board:

| OLED Pin | PCB Header Pin |
|----------|----------------|
| VCC | 3V3 |
| GND | GND |
| SDA | SDA (D4) |
| SCL | SCL (D5) |

The 6 navigation buttons are already soldered to the PCB — no extra wiring needed.

![oled](../../../images/week-11/oled.jpg)

---

### Device 2 — Raspberry Pi Pico W (bare board, no custom PCB)

Just a bare Pico W. No custom board, no extra components. The USB cable powers it and is also what makes it look like a keyboard to the PC.

| Component | Role |
|-----------|------|
| Raspberry Pi Pico W | Connects to ESP_KB WiFi, listens for UDP, types via USB |
| USB cable | Powers the Pico W and presents it as a USB keyboard to the PC |

![device](../../../images/week-11/devices.jpg)

---

## Protocols used

### 1. I2C (Inter-Integrated Circuit)

I2C is how the ESP32-C6 talks to the OLED. Two wires: SDA (data) and SCL (clock). The ESP32 is the main, the SSD1306 is the secondary at address `0x3C`. Every time you update the display, it ships the entire 128×64 pixel buffer (1024 bytes) over those two wires. The Adafruit SSD1306 library handles all the framing — you just call `display.display()`.

Why I2C and not SPI? The SSD1306 supports both, but the 4-pin OLED modules almost always use I2C since it only needs 2 signal wires. Plus the Week 8 PCB already has the I2C header broken out, so it was the obvious choice.

Clock speed is 100kHz by default (standard mode), but the library can push to 400kHz.

---

### 2. WiFi 802.11 (Access Point mode)

The ESP32-C6 runs as a WiFi Access Point — it broadcasts its own network instead of connecting to your home router:

```
SSID     : ESP_KB
Password : 12345678
AP IP    : 192.168.4.1
```

Any device that joins `ESP_KB` gets an IP in the `192.168.4.x` range. The Pico W uses a static IP of `192.168.4.2` so the ESP32 always knows where to send UDP packets.

The ESP32-C6 also supports simultaneous STA (Station) mode — you can have it connect to your home router at the same time. Set `STA_SSID` and `STA_PASS` in the code to enable it.

Why AP mode? Portability. The system works anywhere without needing an existing network. Plug in the two boards and you're good.

---

### 3. UDP (User Datagram Protocol)

UDP is how the ESP32 sends text to the Pico W. When you press SEND on the OLED or hit submit on the web UI, the ESP32 fires off a UDP packet:

```
Source      : 192.168.4.1 (ESP32-C6 AP IP)
Destination : 192.168.4.2:4210 (Pico W static IP, port 4210)
Payload     : raw UTF-8 text + '\n' terminator
Max size    : 200 characters + newline
```

The Pico W keeps a socket open on port `4210` and checks `udp.parsePacket()` every loop (non-blocking). When something arrives, it reads the bytes and starts typing.

Why UDP and not TCP? For short text bursts, UDP is way simpler — no handshake, no connection state to maintain, no retransmit overhead. If a packet gets lost, just press SEND again. The latency is lower too since there's no TCP acknowledgement round-trip.

---

### 4. HTTP (HyperText Transfer Protocol)

The ESP32-C6 runs a minimal HTTP/1.1 web server on port 80 with three endpoints:

#### `GET /`
Returns the full web UI page. The HTML is stored in flash memory (`PROGMEM`) as a raw string — this keeps it from eating into RAM on boot. The page has a `<textarea>`, a Send button, and a status line that auto-refreshes.

#### `POST /send`
The browser posts typed text here as `application/x-www-form-urlencoded`:
```
msg=Hello+World
```
The ESP32 decodes it, forwards it via UDP to the Pico W, and returns `200 OK`.

#### `GET /status`
Returns a small JSON blob:
```json
{"last_sent": "Hello World", "clients": 1}
```
The web page polls this every 2 seconds using `fetch()` and updates the status line without reloading.

Why store HTML in PROGMEM? No filesystem on this board, so the HTML gets compiled directly into flash. Without PROGMEM it would get copied into RAM on boot, which the ESP32-C6 does not have a lot of.

![Desktop UI](../../../images/week-11/desktop-ui.jpg)

![Mobile UI](../../../images/week-11/mobile-ui.jpg)

---
 
### 5. USB HID (Human Interface Device)

This is the part I found genuinely cool. The Pico W tells the PC it's a USB keyboard using the TinyUSB stack (built into the Earle Philhower arduino-pico core). The PC just sees another keyboard — no drivers, no setup.

When a UDP packet arrives, the Pico W loops through each character and calls `Keyboard.write(c)` with a 20ms delay between characters. TinyUSB handles all the USB descriptor negotiation and HID report formatting internally.

Under the hood, HID key reports are 8-byte USB packets:
- Modifier byte (Shift, Ctrl, Alt, etc.)
- Reserved byte
- 6 keycodes (up to 6 simultaneous keys)

`Keyboard.write()` automatically handles uppercase by setting the Shift modifier — you don't deal with that manually.

Why the Pico W and not the ESP32-C6 for this? The ESP32-C6 has no USB OTG hardware — it can only do USB Serial/JTAG (basically just programming and debug). The Pico W's RP2040 has a full USB controller that supports device mode, so it can actually act as a keyboard.

---

## Software architecture

### ESP32-C6 firmware (`esp32_keyboard.ino`)

#### State machine — 3 screens

The OLED cycles through 3 screens with a long-press of SEND (≥1 second):

<video src="../../../images/week-11/Display-States.mp4" controls width="100%"></video>

#### Button input system

All 6 buttons on the Week 8 PCB use `INPUT_PULLUP` (active LOW). The firmware reads each button every loop and applies a 50ms debounce — a state change only registers after the pin has been stable for 50ms. This stops a single press from registering as multiple.

Three timing-based gestures, all using `millis()` with no `delay()`:

| Gesture | Button | Window | Action |
|---------|--------|--------|--------|
| Single press | SPACE | — | Select key under cursor |
| Double press | SPACE | 300ms | Insert literal space |
| Long press | SEND | 1000ms | Cycle to next screen |
| Short press | SEND | <1000ms | Send text buffer via UDP |

Double-press detection logic:
```
On SPACE press:
  If a previous tap was within 300ms → double tap → insert space
  Else → start 300ms timer, wait for second tap

Every loop:
  If timer expired and no second tap → single tap → select key
```

#### OLED rendering (screen 0 — QWERTY)

The 128×64 display is divided into zones:

```
Y=0  ┌────────────────────────────────┐
     │ Q W E R T Y U I O P      CAP  │  ← Row 0 (10 keys, 12px/key)
Y=10 │  A S D F G H J K L            │  ← Row 1 (9 keys, offset 10px)
Y=20 │    Z X C V B N M              │  ← Row 2 (7 keys, offset 22px)
Y=30 │  [CAP]  [BKS]   [SND]         │  ← Row 3 (special keys)
Y=39 ├────────────────────────────────┤  ← separator line
Y=42 │ current text buffer (21 chars) │  ← scrolling text
Y=56 │ Len:12                         │  ← char count / status
     └────────────────────────────────┘
```

The selected key is highlighted by drawing a filled white rectangle and rendering the letter in black (inverted). The display only redraws when a `displayDirty` flag is set — no point hammering I2C every loop if nothing changed.

---

### Pico W firmware (`pico_hid.ino`)

#### Boot sequence
1. Init USB HID keyboard (`Keyboard.begin()`)
2. Configure static IP `192.168.4.2`
3. Connect to `ESP_KB` WiFi AP
4. Open UDP socket on port `4210`

#### Main loop
```
loop():
  If WiFi dropped and 5s elapsed → reconnect
  If UDP packet available:
    Read packet into buffer
    Blink LED (non-blocking, 80ms)
    For each character in buffer:
      Keyboard.write(c)
      delay(20ms)
```

The 20ms per-character delay is necessary — some host OSes can't process HID reports faster than around 50 chars/sec and will just drop keystrokes.

If the ESP32-C6 gets powered off and back on, the Pico W automatically reconnects within 5 seconds without needing a reboot.

---

## Libraries

### ESP32-C6
| Library | Version | Purpose |
|---------|---------|---------|
| Adafruit SSD1306 | 2.5.x | OLED driver |
| Adafruit GFX Library | 1.12.x | Graphics primitives (text, shapes) |
| WiFi.h | built-in (esp32 core) | WiFi AP + STA |
| WebServer.h | built-in (esp32 core) | HTTP server |
| WiFiUDP.h | built-in (esp32 core) | UDP socket |
| Wire.h | built-in | I2C |

### Pico W
| Library | Version | Purpose |
|---------|---------|---------|
| Keyboard.h | built-in (arduino-pico) | USB HID keyboard |
| WiFi.h | built-in (arduino-pico) | WiFi client |
| WiFiUDP.h | built-in (arduino-pico) | UDP socket |

---

## Board manager URLs (Arduino IDE)

| Board | URL |
|-------|-----|
| ESP32 (for XIAO C6) | `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` |
| Pico W (Philhower) | `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json` |

---

## Arduino IDE board settings

### XIAO ESP32-C6
- Board: `XIAO_ESP32C6`
- Upload Speed: 921600
- USB CDC On Boot: Enabled

### Raspberry Pi Pico W
- Board: `Raspberry Pi Pico W`
- USB Stack: **Adafruit TinyUSB** ← this one matters, don't skip it
- Flash Size: 2MB

---

## First boot and test

1. Flash the Pico W with `pico_hid.ino` first
2. Flash the ESP32-C6 (via the Week 8 PCB) with `esp32_keyboard.ino`
3. Power both boards
4. Pico W Serial Monitor (115200 baud) should show:
   ```
   [WiFi] Connected, IP: 192.168.4.2
   [UDP] Listening on port 4210
   ```
5. OLED should show the QWERTY keyboard grid
6. Navigate with the onboard arrow buttons → press SPACE to select a letter → buffer appears at the bottom
7. Short-press SEND → text types itself on your PC via the Pico W
8. Web UI test: connect any device to WiFi `ESP_KB` (password: `12345678`) → open `192.168.4.1` in a browser → type → click Send

---
## Hero Shots

<video src="../../../images/week-11/Hero.mp4" controls width="100%"></video>


## Configuration constants

Everything adjustable is a `#define` at the top of each file:

### `esp32_keyboard.ino`
```cpp
#define AP_SSID   "ESP_KB"          // WiFi network name
#define AP_PASS   "12345678"        // WiFi password
#define STA_SSID  ""               // Home router SSID (leave empty to skip)
#define STA_PASS  ""               // Home router password
#define PICO_IP   "192.168.4.2"    // Pico W static IP
#define PICO_PORT 4210             // UDP port
```

### `pico_hid.ino`
```cpp
#define AP_SSID            "ESP_KB"
#define AP_PASS            "12345678"
#define STATIC_IP          "192.168.4.2"
#define GATEWAY            "192.168.4.1"
#define UDP_PORT           4210
#define CHAR_DELAY_MS      20       // ms between keystrokes
#define RECONNECT_INTERVAL 5000    // ms between reconnect attempts
```

---

## Phase 2 — Two Targets, One Keyboard

The extra credit goal was more than two nodes. Phase 1 was already two devices, but they were asymmetric — one sender, one receiver. For Phase 2 I added a third: a Raspberry Pi Pico 2W, its own static IP, its own USB connection to a second PC. Same keyboard, two machines.

The ESP32-C6 side barely changes — it already runs an AP and fires UDP packets, so you basically just give it a second destination IP to aim at. The real work was on the keyboard side: the OLED needed a client picker screen, the web UI needed target selection buttons, and the numbers row was lowkey long overdue anyway.

![bd-2](../../../images/week-11/bd-2.jpg)

---

### New Hardware — Device 3

| Component | Role |
|-----------|------|
| Raspberry Pi Pico 2W (RP2350) | Second USB HID target — static IP 192.168.4.3 |

No extra wiring. Flash `pico2w_hid.ino`, plug into a second PC via USB, done.

---

### Static IP Assignments

| Device   | IP            | UDP Port |
|----------|---------------|----------|
| ESP32-C6 | 192.168.4.1   | — |
| Pico W   | 192.168.4.2   | 4210 |
| Pico 2W  | 192.168.4.3   | 4210 |

Both Picos listen on port 4210 — different IPs, no conflict.

---

### What Changed on the ESP32-C6

#### Numbers row added

The keyboard now has five rows. `1 2 3 4 5 6 7 8 9 0` sits above the Q-row. Numbers are always numeric — CAPS doesn't touch them, only letters.

```
Y= 0  1 2 3 4 5 6 7 8 9 0
Y= 8  Q W E R T Y U I O P
Y=16  A S D F G H J K L
Y=24  Z X C V B N M
Y=32  [CAP]  [BKS]  [SND]
Y=40  ────────────────────
Y=42  text buffer
Y=55  Len:xx
```

#### Screen cycle — down to two

The Mode screen is gone. Long-pressing SEND now just toggles between the keyboard and the status screen. Honestly two states are way easier to track when you're mid-typing and can't look at code.

| Screen | What it shows |
|--------|---------------|
| 0 — QWERTY | Keyboard + text buffer |
| 1 — Status | AP IP, STA IP, client count, last sent |

#### Client select screen (new)

Short-pressing SEND no longer sends immediately — it opens a picker first. This was necessary because with two possible targets, "send" on its own is ambiguous.

```
┌─────────────────────────────┐
│         Send to:            │
├─────────────────────────────┤
│  >      Pico W              │  ← highlighted when selected
│         Pico 2W             │
│  ^v:sel  SND/SPC:ok  L:bk  │
└─────────────────────────────┘
```

| Button | What it does |
|--------|--------------|
| UP / DOWN | Toggle between Pico W and Pico 2W |
| SEND or SPACE | Confirm — fires UDP to the selected device |
| LEFT | Cancel — back to keyboard, nothing sent |
| Long-press SEND | Skip the picker, jump straight to Status screen |

The on-screen **[SND]** key and the physical SEND button both open the same picker.

---

### What Changed on the Web UI

Two toggle buttons now sit above the Send button — click one to pick your target before sending. **Pico W** (192.168.4.2) is the default. The POST body now includes `&client=0` or `&client=1` so the ESP32 knows which IP to use.

![ui](../../../images/week-11/phase-2-ui.jpg)

---

### New File: `pico2w_hid/pico2w_hid.ino`

This is basically `pico_hid.ino` with one line changed. Literally one constant is different:

```cpp
#define STATIC_IP  "192.168.4.3"   // Pico 2W — Pico W stays on .2
```

Everything else — WiFi connection logic, UDP listener, USB HID output, reconnect handling — is identical. The RP2350 (Pico 2W chip) is backwards compatible with the RP2040 for this use case, so no firmware changes were needed beyond the IP.

#### Arduino IDE settings — Pico 2W

| Setting | Value |
|---------|-------|
| Board | `Raspberry Pi Pico 2 W` |
| USB Stack | **Adafruit TinyUSB** ← same requirement as Pico W |
| Flash Size | 4MB |

---

## Hero Shots

<video src="../../../images/week-11/Hero-2.mp4" controls width="100%"></video>

### Updated Configuration Constants

#### `esp32_keyboard.ino` (Phase 2)
```cpp
#define AP_SSID    "ESP_KB"
#define AP_PASS    "12345678"
#define PICO_IP    "192.168.4.2"   // Pico W
#define PICO2_IP   "192.168.4.3"   // Pico 2W
#define PICO_PORT  4210
```

#### `pico2w_hid.ino`
```cpp
#define AP_SSID            "ESP_KB"
#define AP_PASS            "12345678"
#define STATIC_IP          "192.168.4.3"
#define GATEWAY            "192.168.4.1"
#define UDP_PORT           4210
#define CHAR_DELAY_MS      20
#define RECONNECT_INTERVAL 5000
```


