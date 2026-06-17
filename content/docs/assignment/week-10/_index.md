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

- 

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
