# 🚀 Nadec Biju – Fab Academy 2026 Portfolio

🔗 **Live Site:** https://fabacademy.org/2026/labs/kochi/students/nadec-biju/

---

## 🎬 Final Project Presentation

[![Presentation slide](static/presentation.png)](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/final-project/)

▶️ **[Watch the presentation video](static/presentation.mp4)** — also embedded live on the [Final Project page](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/final-project/)

---

## 👨‍🔧 About Me

Hey! I'm **Nadec Biju**, a Mechanical Engineering student at CUSAT (2022–2026), passionate about:

- Digital Fabrication  
- Robotics & Embedded Systems  
- CAD & Mechanical Design  

I love taking ideas from **"what if?" → "it works."**  
From off-road vehicles to fabrication projects, I focus on building real, functional systems.

---

## 🧠 Skills

- **CAD & Design:** SolidWorks, Fusion 360, Siemens NX  
- **Fabrication:** 3D Printing, Laser Cutting, CNC  
- **Programming:** Python, Arduino, ESP32  
- **Electronics:** Circuit Design, PCB Design  

---

## 🏁 Fab Academy Journey

Fab Academy is a **20-week hands-on digital fabrication program** where each week focuses on a new skill, building toward a final integrated project.

This portfolio documents my **weekly progress, builds, failures, and learnings**.

---

## 🧰 Interactive Tools — Built Along the Way

These are the highlight of this portfolio — actual working tools I built as part of weekly assignments, not just documentation.

| Tool | From | Description |
|---|---|---|
| 📏 **[Laser Kerf Calculator](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/week-3/laser-gauge-tool/)** | Week 3 – CNC Cutting | Calculates laser kerf compensation for precision press-fit joints |
| 🎮 **[NB6-Boy Highscores](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/week-4/nb6-boy/)** | Week 4 – Embedded Programming | Online highscore board for the NB6-Boy handheld game console |
| ⚙️ **[4-Bar Linkage Calculator](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/week-7/chair-4-bar-linkage-calculator/)** | Week 7 – CNC Milling | Solves four-bar linkage geometry for the recliner chair mechanism |
| 👁️ **[Urumi Vision](https://nb6rules.github.io/Urumi-Vision-Web/)** | Computer Vision | Browser-based computer vision web tool |
| 📥 **[Dogbone Plugin Installer](static/files/week-20/Install-Dogbone.bat)** | Week 20 – Fusion CAM | One-click installer for an open-source Fusion 360 dogbone plugin |

---

## 📅 Weekly Assignments

### ✅ Week 01 – Principles & Practices, Project Management
Setting up the tools and systems used for the rest of the program — Git, documentation workflow, and Hugo static site setup.

### ✅ Week 02 – Computer Aided Design
Explored how designs move from 2D to 3D, the difference between raster and vector images, and 3D modeling approaches like B-Rep and F-Rep.

### ✅ Week 03 – Computer Controlled Cutting
Laser cutting and vinyl cutting, kerf testing, and a parametric press-fit construction kit. Built the **Laser Kerf Calculator** tool.

### ✅ Week 04 – Embedded Programming
Programming the XIAO ESP32-C6 for the **NB6-Boy** handheld game console — OLED display, buttons, buzzer, and NeoPixel integration with a custom game in Arduino.

### ✅ Week 05 – 3D Scanning & Printing
Additive manufacturing and reverse engineering through scanning — design rules for 3D printing, printer capability testing, and scanning workflows.

### ✅ Week 06 – Electronics Design
Circuit simulation and schematic/PCB design in KiCad for the NB6-Boy board, including custom footprint import and ERC/DRC validation.

### ✅ Week 07 – Computer Controlled Machining
Designed and fabricated a meter-scale object on a ShopBot CNC router — a Lazy Boy–style recliner chair driven by a four-bar linkage mechanism. Built the **4-Bar Linkage Calculator** tool.

### ✅ Week 08 – Electronics Production
Milled, soldered, programmed, and tested the PCB designed in Week 06 — taking it from design file to a fully functional board.

### ✅ Week 09 – Input Devices
Interfacing sensors with microcontrollers — sensor types, signal conditioning, and data acquisition.

### ✅ Week 10 – Output Devices
Designing a board around an output device — motors, drivers, and power management to make something move.

### ✅ Week 11 – Networking and Communications
Built a wireless QWERTY keyboard system — wired/wireless nodes with network addressing and local I/O.

### ✅ Week 12 – Mechanical Design (Machine Week, Part 1)
Designing mechanisms and motion systems as part of the machine-building project.

### ✅ Week 13 – Midterm Review
Final project checkpoint — turning the project idea into a concrete plan with deliverables for instructor review.

### ✅ Week 14 – Molding and Casting
Designed a mold, machined it into wax, cast a silicone negative, and produced a final resin part.

### ✅ Week 15 – Interface and Application Programming
Building user interfaces that communicate with embedded systems.

### ✅ Week 16 – System Integration
Bringing together electronics, programming, and fabrication into a cohesive functional system.

### ✅ Week 17 – Wildcard Week
Exploring a fabrication process outside the regular curriculum to support the final project. Includes the **Tool Trace** foam cutout workflow.

### ✅ Week 18 – Applications and Implications
Detailed planning of the final project and its broader impact.

### ✅ Week 19 – Invention, Intellectual Property, and Income
Figuring out IP, licensing, and how the final project design could (or couldn't) be used by others.

### 🔧 Project Development (Weeks 18–20)
The full build log for the final project — mechanical design of the tool cabinet, 5 custom PCBs (XIAO main board, XIAO sister board, drawer board, NEOBUTTON and NEOHALL-EFFECT nodes), Carvera CNC milling, foam tool cutouts, and ShopBot routing of the plywood cabinet structure. Built the **Dogbone Plugin Installer** tool along the way.

---

## 🚧 Final Project — Smart Tool Cabinet with RFID Tracking

A **Smart Tool Cabinet** that tracks tools using RFID cards for access control, with mini switches and individual microcontrollers in each tool slot to detect when tools are removed.

### What It Does
- **RFID Access Control** – Each person gets an RFID card to unlock drawers they're trained to use
- **Tool Tracking** – Mini switches in each tool slot log when tools are taken and returned
- **Automatic Alerts** – System alerts if tools aren't returned on time
- **Usage Logging** – Tracks who used what and when

### Components
**Hardware:** RFID reader & cards, mini switch sensors, solenoid locks, XIAO ESP32-C6 + CH32V003J4M6 microcontrollers, custom-fabricated enclosure
**Software:** RFID authentication, switch monitoring & data logging, alert system, mobile app (iOS and Android)

Full build log: [Project Development](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/project-development/) · Full writeup: [Final Project page](https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/final-project/)

---

## 📚 What I Learned

- Designing is only **half the job** — manufacturing matters  
- Iteration and failure are critical  
- Documentation = reproducibility  
- Integration is the hardest (and most important) step  

---

## 🧑‍💼 Experience Highlights

- **Team Captain – Tarusa Motorsports**  
- **Design Lead – Hermes CUSAT**  
- **Intern – Indian Racing League / Formula 4**  
- **Founding Intern – Pre6 (AI Startup)**  

---

## 💭 Philosophy

> “Engineering isn’t just theory — it’s building things that move, fail, and finally work.”

---

## ⚡ Author

**Nadec Biju**  
Mechanical Engineer | Builder | Problem Solver  
