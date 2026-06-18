+++
title = "Week 10 - Output Devices"
weight = 110
bookCollapseSection = true
+++

# Week 10 - Output Devices

Week 10 was all about **output devices**, the flip side of last week. If Week 9 was about sensing the world, this week was about *acting* on it. Motors, drivers, power management, and actually making something move.

The assignment: design a board with an output device, then program it to do something.

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

- 

---

## Software Used
- **KiCad**: schematic + PCB layout
- **Arduino IDE**: firmware
- **Mods CE**: CAM for PCB milling
- **Browser + Git**: documentation

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on output devices |
| THU | Group Assignment, power measurement |
| FRI | Selecting output devices, reading ESP32-WROOM-32E datasheet |
| SAT | DRV8825 datasheet deep-dive, schematic design in KiCad |
| SUN | PCB layout, single DRV design|
| MON | Milling, soldering, testing |
| TUE | Regional review |

---
# Group Assignment

For this group assignment, we measured power consumption hands-on instead of just trusting the numbers in a datasheet. We hooked up a bench power supply and a digital multimeter to a couple of output devices and read off the actual current they pulled while running.

The math behind it is simple Ohm's law territory:

Power (W) = Voltage (V) × Current (A)

**NeoPixel:**

| Measurement | Value |
|---|---|
| Supply Voltage | 5 V |
| Measured Current | 0.0337 A |
| Power | 5 × 0.0337 = 0.1685 W |

![NeoPixel power measurement setup](../../../images/week-10/01.jpg)

**Stepper motor:**

| Measurement | Value |
|---|---|
| Supply Voltage | 5 V |
| Measured Current | 0.011 A |
| Power | 5 × 0.011 = 0.055 W |

![Stepper motor power measurement setup](../../../images/week-10/02.jpg)


The main thing I took from this is how to hook a multimeter in series to get a real current reading, and how that one number turns into a power figure once you multiply it by the voltage. Knowing the actual draw of a part, not just the datasheet guess, matters a lot when you're picking a battery or sizing a power supply for an embedded project. Get it wrong and you either run out of juice fast or carry around a way bigger battery than you need.

Source: https://fabacademy.org/2026/labs/kochi/group_assignmetns/week10/

---

# Individual Assignment

## Output Device Selection

This week's goal was to build a stepper motor tester. I got the idea from my instructor [Sibin K S](https://fabacademy.org/2023/labs/kochi/students/sibin-ks/). He told me that servo testers already exist, little tools that let you check if a servo works without hooking it up to a microcontroller, running jumper wires, and writing Arduino code just to find out if it's dead. We didn't have anything like that at our lab for stepper motors. So he suggested building a stepper motor tester that could do the same job: quickly check if a stepper motor works, with no microcontroller wiring or code needed on the spot.

For a future version, I'm planning to add an INA219 chip so I can graph things like current draw versus RPM on a web app.

The stack I landed on:

| Component | Part |
|---|---|
| Microcontroller | ESP32-WROOM-32E |
| Motor driver | DRV8825 |
| Motor | NEMA 17 bipolar stepper |

I picked the ESP32-WROOM-32E because it has WiFi, which means I could control the stepper motor wirelessly down the road, and it has plenty of GPIO pins to run more than one DRV8825 driver if I want to grow this project later. I picked the DRV8825 because it's a well-known stepper motor driver that can handle what a NEMA 17 motor needs, and it has microstepping built in. I picked the NEMA 17 motor because it's a common size for hobby projects and gives a good mix of torque and speed for testing.

---

## The Components

### ESP32-WROOM-32E — Microcontroller Module

<div style="display: flex; gap: 10px;">
  <img src="../../../images/week-10/1.jpg" alt="ESP32-WROOM-32E module" style="width: 50%;">
  <img src="../../../images/week-10/2.jpg" alt="ESP32-WROOM-32E pinout" style="width: 50%;">
</div>


The **ESP32-WROOM-32E** is a surface-mount WiFi + Bluetooth module from Espressif, built around the ESP32-D0WD-V3 chip. I picked it over the XIAO or ATtiny for a few reasons:

- It has enough GPIO to run five DRV8825 drivers at once (STEP, DIR, ENABLE per driver means 15 pins minimum). For me this was relevant as i wanted to built a wroom based board in the future to control five stepper motors at once, for a future project . Shhh.......
- Built-in WiFi gives me wireless control options for the final project
- It has a strong Arduino/ESP-IDF ecosystem, with libraries for almost everything
- It's likely what the final project will use anyway, so this week doubles as practice

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

> The above specs are found from the ESP32-WROOM-32E datasheet and curated using Claude by Anthropic.

**Minimum circuit:**

I went through the ESP32-WROOM-32E datasheet properly, not just the pinout but the *application circuit* section too. The minimum circuit needs:

- **3.3 V regulated supply** with bulk and bypass decoupling (100 µF + 100 nF on VDD)
- **EN pin** pulled HIGH through a 10 kΩ resistor (the module won't boot if EN is left floating)
- **IO0 pin** pulled HIGH through a 10 kΩ resistor for normal boot, or pulled LOW to enter download mode
- **UART0** (TX = GPIO1, RX = GPIO3) brought out for programming through a USB-UART bridge (CP2102 or CH340)
- **Boot button** on IO0 and a **Reset button** on EN, both needed for programming to work reliably

This is the stuff that gets skipped when you use a ready-made dev board. Building it from scratch forces you to actually understand what the chip needs to run.

![ESP32-WROOM-32E minimum circuit schematic](../../../images/week-10/esp-minimum-circuit.jpg)

---

### DRV8825 — Stepper Motor Driver

![DRV8825 stepper motor driver module](../../../images/week-10/3.jpg)

The **DRV8825** is a bipolar stepper motor driver IC from Texas Instruments. It handles all the H-bridge switching on its own. You just send STEP pulses and a DIR signal from the microcontroller, and the IC drives the motor coils at whatever current you've set.

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

> The above specs are found from the DRV8825 datasheet and curated using Claude by Anthropic.

**How it works:**

The DRV8825 has two H-bridge outputs, one for each motor coil (coil A and coil B). Each H-bridge can push and pull current, which is exactly what bipolar stepper control needs. You set the **current limit** by turning a potentiometer on the VREF pin.

The **microstepping** resolution is set with three pins: MODE0, MODE1, MODE2. Setting them LOW or HIGH in different combinations selects anything from full-step to 1/32 step.

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

> ⚠️ **The 100 µF capacitor on VMOT is not optional.** The DRV8825 datasheet says so directly. When the motor slows down, it acts like a generator and pushes current back into VMOT. Without the cap, that voltage spike can go past the driver's absolute maximum rating and kill the IC instantly. (**I'm using a 470uf cap on my board, just to be safe.**)

---

### NEMA 17 — Bipolar Stepper Motor

![NEMA 17 motor](../../../images/week-10/4.jpg)

**What is a stepper motor?**

A stepper motor is a brushless DC motor that splits a full rotation into a fixed number of steps. A regular DC motor just spins when you give it voltage, but a stepper motor moves in small, repeatable steps, which makes it great for position control without needing a feedback sensor.

**Types of stepper motors:**

| Type | Description | Wires |
|---|---|---|
| **Unipolar** | Has a center tap on each coil — simpler driver circuit, lower torque | 5 or 6 wires |
| **Bipolar** | No center tap — both coil ends driven by the driver, higher torque, needs H-bridge | 4 wires |
| **Variable reluctance** | Uses soft iron rotor, no permanent magnets — fast but low torque | — |
| **Hybrid** | Most common — combines permanent magnet + toothed rotor for high resolution | 4 wires |

**Why NEMA 17?**

NEMA 17 is just a mechanical frame standard. It sets the faceplate size (42.3 × 42.3 mm, 4 mounting holes on a 31 mm bolt circle), not the motor's electrical specs. But in practice, NEMA 17 motors are almost always bipolar hybrid steppers, and that combination is what made it the right pick:

- **1.8° per step** (200 steps per revolution), a standard resolution that works well with DRV8825 microstepping
- **High torque-to-size ratio**, enough torque for most mechanical jobs without jumping up to a bulkier NEMA 23
- **Widely available, cheap, well-documented**, with a huge ecosystem of mounts, pulleys, and couplers
- **4-wire bipolar**, which plugs straight into the DRV8825 with no center tap to worry about

**The four wires — coil identification:**

A bipolar NEMA 17 has four wires that make up two coils:

| Wire | Label | Function |
|---|---|---|
| **Coil A+** | A1 | One end of coil A |
| **Coil A−** | A2 | Other end of coil A |
| **Coil B+** | B1 | One end of coil B |
| **Coil B−** | B2 | Other end of coil B |

The driver fires coil A and coil B in sequence, and the pull between the rotor magnets and the energized coils drags the rotor into each new step position. Direction is set by reversing the order the coils are fired in, which is exactly what the DIR pin on the DRV8825 controls.

To figure out which wires belong to the same coil, I used a multimeter set to continuity or resistance mode. Wire pairs with low resistance (around 1–5 Ω) are the same coil. Pairs with no continuity belong to different coils.

---

## Board Design

Once I understood all my parts and how they worked, I moved on to actually designing the board. I used KiCad to draw the schematic, lay out the PCB, and check the 3D model before sending it off to be milled.

### Schematic

![KiCad schematic — ESP32 + five DRV8825 drivers](../../../images/week-10/5.jpg)

### PCB Layout

![PCB layout — five DRV8825 board](../../../images/week-10/6.jpg)

### 3D View

![3D view of the board](../../../images/week-10/7.jpg)

---

## Manufacturing

- Milling machine: Carvera
- Substrate: FR1 double-sided copper clad
- Trace width / clearance: 0.6 mm / 0.4 mm (logic), 1.1 mm (motor power traces)
- Tool: 0.2 mm 60° V-bit (traces), 1/32" flat end mill (outline)
- Software: Mods CE

**Bill of Materials:**

| Component | Value | Qty |
|-----------|-------|-----|
| C1, C5 | 4.7uF | 2 |
| C2, C4, C7 | 0.1uF | 3 |
| C3 | 10uF | 1 |
| C6 | 1uF | 1 |
| C8 | 100uF | 1 |
| D1, D2, D3 | LED | 3 |
| J1 | PROG header (2x03) | 1 |
| J2 | 1x04 header | 1 |
| J3 | Screw terminal 1x02 | 1 |
| R1, R3, R4 | 10K | 3 |
| R2, R6 | 1k | 2 |
| R5 | R220 | 1 |
| R7, R8 | 4.7K | 2 |
| SW1 | Push button | 1 |
| SW2 | NDS-03V switch | 1 |
| U1 | AMS1117-3.3 | 1 |
| U2 | ESP32-WROOM-32E | 1 |
| U3 | DRV8825 carrier | 1 |

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

- The minimum circuit section of the ESP32-WROOM-32E datasheet is easy to miss but really important. Skipping the EN and IO0 pull-up resistors is the kind of mistake that comes back to bite you, since the module just won't boot reliably without them.
- The 100 µF (470 µF in my case) cap on VMOT isn't just a nice-to-have. The motor really does act like a generator when it slows down, and the voltage spike happens too fast to catch with a scope in time to save the driver.
- Figuring out which wires belong to which coil on the NEMA 17 with a multimeter, before wiring anything up, takes two minutes and saves a lot of frustration later.
