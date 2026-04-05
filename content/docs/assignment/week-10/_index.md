+++
title = "Week 10 - Output Devices"
weight = 110
bookCollapseSection = true
+++

# Week 10 - Output Devices

Week 10 was all about **output devices** — the flip side of last week. If Week 9 was about sensing the world, this week was about *acting* on it. Motors, drivers, power management, and actually making something move.

The assignment: design a board with an output device, program it to do something.

---

## Group Assignment
- Measure the **power consumption** of an output device

## Individual Assignment
- Add an **output device** to a microcontroller board you've designed, and program it to do something

**Extra Credit Goals**
- Try **multiple output types**
- Implement **PWM control** or other modulation techniques

---

## What I Learned

- How to read a microcontroller datasheet properly — specifically the minimum operating circuit for the ESP32-WROOM-32E, which is more involved than most dev boards let you believe
- How the DRV8825 actually drives a stepper motor — current limiting, microstepping, and why the DECAY pin matters
- The difference between stepper motor types (unipolar vs bipolar) and why bipolar is the right call for precision motion control
- How NEMA 17 coil wiring works — identifying coil A and coil B pairs from a four-wire motor
- PCB layout considerations for mixed-signal boards with both logic (3.3 V) and power (12 V motor supply) domains
- Why you need a bulk decoupling capacitor right at the DRV8825 VMOT pin — and what happens if you skip it

---

## Software Used
- **KiCad** — schematic + PCB layout
- **Arduino IDE** — firmware
- **Mods CE** — CAM for PCB milling
- **Browser + Git** — documentation

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on output devices |
| THU | Group Assignment — power measurement |
| FRI | Selecting output devices, reading ESP32-WROOM-32E datasheet |
| SAT | DRV8825 datasheet deep-dive, schematic design in KiCad |
| SUN | PCB layout — single DRV design, then redesigned to five DRV |
| MON | Milling, soldering, testing |
| TUE | Regional review |

---

## Output Device Selection

The goal for this week was to drive a **stepper motor**. Specifically I wanted a setup that could control motor position precisely — relevant to my final project — rather than just blinking an LED or driving a buzzer.

The stack I landed on:

| Component | Part |
|---|---|
| Microcontroller | ESP32-WROOM-32E |
| Motor driver | DRV8825 |
| Motor | NEMA 17 bipolar stepper |

---

## The Components

### ESP32-WROOM-32E — Microcontroller Module

The **ESP32-WROOM-32E** is a surface-mount WiFi + Bluetooth module from Espressif built around the ESP32-D0WD-V3 chip. I chose this over the XIAO or ATtiny because:

- It has enough GPIO to run five DRV8825 drivers simultaneously (STEP, DIR, ENABLE per driver = 15 pins minimum)
- Built-in WiFi opens up wireless control options for the final project
- Strong Arduino/ESP-IDF ecosystem — libraries for everything
- It's what the final project will likely use anyway, so this week is good practice

**Key specs:**

| Parameter | Value |
|---|---|
| CPU | Xtensa dual-core LX6, up to 240 MHz |
| Flash | 4 MB (on-module) |
| RAM | 520 KB SRAM |
| WiFi | 802.11 b/g/n (2.4 GHz) |
| Bluetooth | BT 4.2 + BLE |
| GPIO | 38 pins |
| ADC | 18 channels, 12-bit |
| PWM | Ledc peripheral — 16 channels |
| Supply voltage | 3.0 – 3.6 V (module) |
| Programming | USB-UART bridge + EN/IO0 boot pins |

**Minimum circuit:**

Going through the ESP32-WROOM-32E datasheet properly — not just the pinout, but the *application circuit* section — the minimum circuit requires:

- **3.3 V regulated supply** with bulk and bypass decoupling (100 µF + 100 nF on VDD)
- **EN pin** pulled HIGH via 10 kΩ resistor (module won't boot if EN floats)
- **IO0 pin** pulled HIGH via 10 kΩ for normal boot, pulled LOW to enter download mode
- **UART0** (TX = GPIO1, RX = GPIO3) brought out for programming via USB-UART bridge (CP2102 or CH340)
- **Boot button** on IO0 and **Reset button** on EN — both needed for reliable programming

This is the stuff that gets skipped when you use a pre-made dev board. Designing it from scratch forces you to understand what the chip actually needs to run.

![ESP32-WROOM-32E minimum circuit schematic](../../../images/week-10/esp-minimum-circuit.jpg)

---

### DRV8825 — Stepper Motor Driver

The **DRV8825** is a bipolar stepper motor driver IC from Texas Instruments. It handles all the H-bridge switching internally — you just send STEP pulses and a DIR signal from the microcontroller, and the IC drives the motor coils at whatever current you've set.

**Key specs:**

| Parameter | Value |
|---|---|
| Motor supply voltage | 8.2 – 45 V |
| Output current | Up to 2.5 A per coil (with heatsink) |
| Microstepping | Full, 1/2, 1/4, 1/8, 1/16, 1/32 |
| Logic supply | 3.3 V / 5 V compatible |
| Interface | STEP / DIR / ENABLE |
| Thermal shutdown | Yes |
| Overcurrent protection | Yes |

**How it works:**

The DRV8825 has two H-bridge outputs — one per motor coil (coil A and coil B). Each H-bridge can source and sink current, which is what bipolar stepper control requires. You set the **current limit** by adjusting a potentiometer on the VREF pin — the formula is:

The **microstepping** resolution is set via three pins: MODE0, MODE1, MODE2. Tying them LOW/HIGH in different combinations selects full-step through 1/32 step.

**Pin connections from datasheet:**

| Pin | Function |
|---|---|
| VMOT | Motor power supply (8.2–45 V) — **100 µF cap mandatory here** |
| GND | Power ground |
| VDD | Logic supply (3.3 V) |
| STEP | Step pulse input — one rising edge = one step |
| DIR | Direction — HIGH/LOW sets rotation direction |
| ENABLE | Active LOW — pull LOW to enable outputs |
| MODE0/1/2 | Microstepping select |
| FAULT | Active LOW fault output (overcurrent, thermal) |
| RESET | Active LOW reset — pull HIGH for normal operation |
| SLEEP | Active LOW sleep — pull HIGH for normal operation |
| B2, B1 | Coil B outputs |
| A2, A1 | Coil A outputs |

> ⚠️ **The 100 µF capacitor on VMOT is not optional.** The DRV8825 datasheet explicitly states it — when the motor decelerates, it acts as a generator and dumps current back into VMOT. Without the cap, this voltage spike can exceed the driver's absolute maximum rating and kill the IC instantly.

---

### NEMA 17 — Bipolar Stepper Motor

**What is a stepper motor?**

A stepper motor is a brushless DC motor that divides a full rotation into a fixed number of discrete steps. Unlike a regular DC motor that just spins when you apply voltage, a stepper motor moves in precise, repeatable increments — making it ideal for position control without a feedback sensor.

**Types of stepper motors:**

| Type | Description | Wires |
|---|---|---|
| **Unipolar** | Has a center tap on each coil — simpler driver circuit, lower torque | 5 or 6 wires |
| **Bipolar** | No center tap — both coil ends driven by the driver, higher torque, needs H-bridge | 4 wires |
| **Variable reluctance** | Uses soft iron rotor, no permanent magnets — fast but low torque | — |
| **Hybrid** | Most common — combines permanent magnet + toothed rotor for high resolution | 4 wires |

**Why NEMA 17?**

NEMA 17 is a mechanical frame standard — it defines the faceplate dimensions (42.3 × 42.3 mm, 4 mounting holes on a 31 mm bolt circle). It doesn't define the motor's electrical specs, but in practice NEMA 17 motors are almost always bipolar hybrid steppers with the following characteristics that made it the right choice:

- **1.8° per step** (200 steps per revolution) — standard resolution, compatible with DRV8825 microstepping
- **High torque-to-size ratio** — enough torque for most mechanical applications without going to a bulkier NEMA 23
- **Widely available, cheap, well-documented** — huge ecosystem of mounts, pulleys, couplers
- **4-wire bipolar** — directly compatible with the DRV8825, no center tap complications

**The four wires — coil identification:**

A bipolar NEMA 17 has four wires corresponding to two coils:

| Wire | Label | Function |
|---|---|---|
| **Coil A+** | A1 | One end of coil A |
| **Coil A−** | A2 | Other end of coil A |
| **Coil B+** | B1 | One end of coil B |
| **Coil B−** | B2 | Other end of coil B |

The driver energizes coil A and coil B in sequence, and the interaction between the rotor magnets and the energized coils pulls the rotor to each new step position. Direction is controlled by reversing the current sequence through the coils — which is what the DIR pin on the DRV8825 does.

To identify which wires form a coil pair: use a multimeter in continuity or resistance mode. Wire pairs that show low resistance (~1–5 Ω typically) are the same coil. Pairs with no continuity are from different coils.

---

## Board Design

### The Plan — Why It Changed

I started the design with **one DRV8825 and one NEMA 17** — simple, straightforward, enough to meet the assignment.

After going through the schematic and verifying everything was correct, I reconsidered. My final project is going to need multiple motors running simultaneously. If I'm already designing a board this week, why not scale it up to something actually useful — a **five-DRV8825 board** capable of driving five NEMA 17 motors independently?

So I redesigned.

**Five-driver board spec:**
- ESP32-WROOM-32E as the main controller
- Five DRV8825 driver slots — plug-in module footprint (standard 2×4 pin header)
- Shared VMOT rail (12 V) with individual 100 µF caps per driver
- Shared 3.3 V logic rail from onboard LDO
- STEP, DIR, ENABLE lines from ESP32 GPIOs to each driver
- Screw terminal connectors for each motor's four wires
- UPDI-style programming header (UART TX, RX, EN, IO0, GND, 3V3)

### Schematic

![KiCad schematic — ESP32 + five DRV8825 drivers](../../../images/week-10/    .jpg)

### PCB Layout

![PCB layout — five DRV8825 board](../../../images/week-10/output-   .jpg)

### 3D View

![3D view of the board](../../../images/week-10/output   .jpg)

---

## Manufacturing

- Milling machine: Roland MDX-20
- Substrate: FR1 single-sided copper clad
- Trace width / clearance: 0.4 mm / 0.4 mm (logic), 0.8 mm (motor power traces)
- Tool: 0.2 mm 60° V-bit (traces), 1/32" flat end mill (outline)
- Software: Mods CE

**Bill of Materials:**

| Component | Value | Qty |
|---|---|---|
| ESP32-WROOM-32E | — | 1 |
| DRV8825 module | — | 5 |
| Capacitor, electrolytic | 100 µF / 35 V | 5 (one per VMOT) |
| Capacitor, ceramic | 100 nF | multiple (decoupling) |
| Resistor | 10 kΩ | 2 (EN, IO0 pull-ups) |
| LDO regulator | 3.3 V | 1 |
| Screw terminals | 4-pin | 5 (one per motor) |
| Pin headers | 2×4 | 5 (DRV8825 sockets) |
| USB-UART bridge | CP2102 or CH340 | 1 |

---

## Programming



---

## Code

```cpp

```

---

## Results



---

## Files



## Reflections

- Scaling from one DRV to five mid-design was the right call — the routing got more complex but the result is actually useful hardware, not just a week assignment.
- The minimum circuit section of the ESP32-WROOM-32E datasheet is genuinely non-obvious. The EN and IO0 pull-up resistors are the kind of thing that bites you if you skip them — the module just won't boot reliably.
- The 100 µF cap on VMOT isn't just a suggestion. The motor-as-generator behaviour during deceleration is real and the voltage spike is fast enough that you'd never catch it with a scope in time to save the driver.
- Identifying coil pairs on the NEMA 17 with a multimeter before wiring anything up is a two-minute step that saves a lot of frustration.
