+++
title = "Week 06 - Electronics Design"
weight = 106
bookCollapseSection = true
+++

# Week 06 – Electronics Design

Week 6 is all about **Electronics Design** — which basically means this is the week where we stop connecting stuff on breadboards and start actually *designing* the circuits ourselves. The goal was to understand how to simulate circuits, draw proper schematics, and route a real PCB.

I tied this week directly into the NB6-Boy project I built during the Embedded Programming week, so this was super relevant for me.

-----

## Group Assignment

- Use the test equipment in your lab to observe the operation of a microcontroller circuit board

## Individual Assignment

- Use an **EDA tool** to design a development board that can interact with and send data to an embedded microcontroller
- Extra Credit: Try different tools

-----

## What I Learned

This week helped me understand the full electronics design pipeline — from how a circuit is *simulated* before it’s built, all the way through to how you *route a PCB* and visualise it in 3D.

Key things I picked up:

- How Wokwi works as a circuit simulator and why the VS Code plugin is better for complex projects
- How to create a full schematic in KiCad with proper symbols and net connections
- How to import custom component footprints from SnapMagic when the standard library doesn’t have what I need
- How ERC/DRC checks can save you from expensive mistakes
- How to go from a KiCad PCB all the way into Fusion 360 for casing design using a STEP file export

-----

## Software Used

- **Wokwi** (browser + VS Code plugin) — circuit simulation
- **KiCad** — schematic and PCB design
- **SnapMagic** — importing custom component footprints
- **Fusion 360** — 3D casing design using exported STEP file

-----

## Weekly Schedule

|Day|What I Did                                                   |
|---|-------------------------------------------------------------|
|WED|Lecture on electronics design with Neil                      |
|THU|Wokwi browser simulation — building the NB6-Boy circuit      |
|FRI|Switching to Wokwi VS Code plugin, getting simulation working|
|SAT|KiCad install, Fab library setup, starting the schematic     |
|SUN|Completing schematic, ERC check, assigning footprints        |
|MON|PCB layout, routing, DRC, 3D view and STEP export            |
|TUE|Regional review                                              |

-----

## Group Assignment - Test Equipment and Observations

For the group assignment this week, we explored the essential test equipment available in the lab and used them to observe and analyse a working microcontroller circuit. The goal was to go beyond theoretical knowledge and actually *see* how signals behave in real electronic systems.

Here's a quick rundown of the equipment we worked with:

### 🔬 Multimeter (ZOYI ZT301)
The multimeter was used for the basics — checking continuity across PCB traces, measuring voltage on the 3.3V and 5V rails, and verifying resistor values. Honestly one of the most useful tools in the lab because it's so fast to grab and check if something is actually connected or powered.

Key tests we ran:

* **Continuity check** — to verify traces and solder joints before powering anything up (beep = connected, no beep = check your soldering lol)
* **Voltage measurement** — confirmed 3.3V and 5V rails were correct on the microcontroller board
* **Resistance measurement** — verified component values matched what was on the schematic

### 📡 Oscilloscope (OWON TAO3104A)

This is where it got really interesting. We used a **Seeed Studio XIAO RP2040** as a software-defined function generator to output different waveforms via PWM, and then observed them live on the oscilloscope.

Waveforms we generated and captured:

* Sine wave
* Square wave (50% duty cycle)
* Triangle wave
* Sawtooth / Ramp
* Pulse 25% and Pulse 10%

> **Important note:** Since the RP2040 outputs digital PWM signals, waveforms like sine and triangle are *approximations* — the shape is created by rapidly varying the pulse width over time. You need to zoom out on the time/div scale to see the overall envelope rather than individual pulses.

### 🔌 Logic Analyser (Saleae Logic 8)

We also used the **Saleae Logic 8** to capture and decode real communication protocols from the RP2040. This was genuinely eye-opening — seeing actual bytes being transmitted and automatically decoded in the software is a completely different experience from just reading about protocols in theory.

* **UART capture** — decoded "hello world!" transmitted via Serial1 at 9600 baud
* **I²C capture** — captured the communication between the RP2040 and an SSD1306 OLED display, including the START condition, 7-bit device address (0x3C → 0x78 on the bus), ACK bits, and data bytes

### ⚡ Bench Power Supply

Used to provide clean, regulated DC power to circuits during testing — set the voltage, set a current limit to protect the board, and you're good to go. Way safer than just plugging things into USB when you're not sure if your circuit is correct yet.

---

Check out the full group documentation for all the waveform captures, code, and protocol decoding breakdowns:  
🔗 [https://fabacademy.org/2026/labs/kochi/group_assignmetns/week06/](https://fabacademy.org/2026/labs/kochi/group_assignmetns/week06/)

---

# Part 1 – Circuit Simulation with Wokwi

## 🖥️ What is Wokwi?

**[Wokwi](https://wokwi.com/)** is a free, browser-based electronics simulator that lets you test circuits and code *before* you ever touch actual hardware.

It supports a ton of microcontrollers (ESP32, RP2040, Arduino, etc.) and common components — and it’s completely free to use. Think of it like a virtual breadboard + compiler combo.

This is actually really useful because you can catch wiring mistakes and code bugs without burning components or wasting time debugging hardware.

-----

## 🆕 Creating an Account and New Project

**Steps:**

1. Go to [wokwi.com](https://wokwi.com/)
1. Click **Sign Up** and create a free account (you can use email or GitHub)
1. Once logged in, click **New Project**
1. From the template picker, select **XIAO ESP32-C6** as the starting board

![Wokwi New Project](../../../images/week-6/wokwi-new-project.jpg)

> **Why XIAO ESP32-C6?** — My NB6-Boy from Week 4 was built on the Seeed Studio XIAO ESP32-C6, so I needed to simulate with the exact same board to use the same code and wiring.

-----

## ➕ Adding Components in the diagram.json

Wokwi stores your circuit inside a file called **`diagram.json`**. You can either edit it as JSON directly or use the visual drag-and-drop interface — I used the visual interface since it’s way easier.

**Components I added for the NB6-Boy:**

|Component             |Quantity|Purpose                                    |
|----------------------|--------|-------------------------------------------|
|XIAO ESP32-C6         |1       |Main microcontroller                       |
|Push Buttons          |6       |Game controls (Up, Down, Left, Right, A, B)|
|Passive Buzzer        |1       |Sound effects and audio feedback           |
|OLED Display (SSD1306)|1       |Game display                               |
|NeoPixel LED Matrix   |1       |Visual effects and score display           |

**How to add components:**

1. Click the **"+"** button (Add Component) in the top toolbar
1. Search by name — e.g. type `pushbutton`, `buzzer`, or `SSD1306`
1. Click to place it on the canvas
1. Drag it to wherever makes sense in your layout
1. Click on a pin to start drawing a wire, then click the destination pin to finish the connection
1. Repeat for all your components until everything is wired up

![Wokwi Components Added](../../../images/week-6/wokwi-components.jpg)

![Wokwi Components Added](../../../images/week-6/wokwi-components-1.jpg)

-----

## 💻 Pasting the Code and Simulating

Once the wiring was done:

1. Click the **code editor tab** on the left panel — this is the `.ino` file section
1. Paste in the full NB6-Boy code from Week 4
1. Hit the **▶ Simulate** button

**Problem:** The online compiler timed out with a long string of `000...` errors and couldn't finish compiling. This was because Wokwi's compilation server was being heavily utilised by a lot of other users at the time.

Since I couldn't simulate on that day, I decided to switch to a different approach while waiting — the Wokwi VS Code plugin.

**Update:** After 2 days, I tried the browser simulation again and it worked perfectly! The server load had gone down and my circuit simulated without any issues.

<iframe
  src="https://wokwi.com/projects/457467088374687745"
  width="100%"
  height="400"
  frameborder="0"
  allowfullscreen>
</iframe>

-----

## 🔌 Switching to the Wokwi VS Code Plugin

While waiting for the browser compiler to become available, I decided to try the **Wokwi VS Code extension** — it uses your *local* compiler instead of the browser's online one, so you're not dependent on server availability.

### Installing the Extension

1. Open **VS Code** and go to the Extensions panel (`Ctrl+Shift+X`)
1. Search for **Wokwi** and install the official **Wokwi Simulator** extension

![Wokwi VS Code Extension](../../../images/week-6/wokwi-vscode.jpg)

1. Once installed, you’ll be prompted to activate it — click the link and follow the steps on the [official Wokwi VS Code docs](https://docs.wokwi.com/vscode/getting-started) to get your free licence key
1. Paste the key into VS Code when prompted and you’re good to go

-----

### Setting Up the Project

1. Open your project folder in VS Code (the one containing your `.ino` or PlatformIO source)
1. Create a `wokwi.toml` file in the root of your project:

```toml
[wokwi]
version = 1
elf = ".pio/build/esp32dev/firmware.elf"
firmware = ".pio/build/esp32dev/firmware.bin"
```

1. Copy the `diagram.json` file you built on the Wokwi website into the same project folder
1. Make sure your source code is in the `src/` folder (if using PlatformIO) or directly in the project root (if using Arduino CLI)

-----

### Running the Simulation

1. Press **`F1`** and type **Wokwi: Start Simulator** — or click the Wokwi icon in the sidebar
1. VS Code compiles the code locally first
1. Once done, the simulation window opens

<video width="100%" controls>
  <source src="../../../images/week-6/wokwi-vscode-running.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

**Result:** The NB6-Boy simulation worked perfectly in VS Code! 🎮

The OLED display booted up, all six buttons were responsive, the NeoPixel matrix lit up, and the buzzer fired sounds exactly like it does on the physical hardware.

> **Tip:** The VS Code plugin is a great alternative when the browser compiler is busy or unavailable. It also gives you better control over your build environment since compilation happens locally.

-----

# Part 2 – Schematic Design with KiCad


## Recreating Neil's ATtiny412 Example Design

As part of our KiCad training, our instructor **[Saheen Palayi](https://fabacademy.org/2021/labs/kochi/students/saheem-palayi/)** guided us through recreating one of Neil's example designs. I went through the **[Fab Academy Embedded Programming class notes](https://fabacademy.org/2026/classes/embedded_programming/index.html)** — Neil covers a ton of processor families, architectures, and example designs in there, and this training session helped me actually apply the concepts rather than just reading through them.

One of the designs Neil references is a minimal **ATtiny412** board, so under [Saheen](https://fabacademy.org/2021/labs/kochi/students/saheem-palayi/)'s guidance, I recreated my own version of it in KiCad — a clean, simple development board built around the ATtiny412 (8-bit AVR 1-series, runs at up to 20 MHz, single-wire UPDI programming).

### Schematic

![ATtiny412 Schematic](../../../images/week-6/attiny412-schematic.jpg)

### PCB Layout

![ATtiny412 PCB](../../../images/week-6/attiny412-pcb.jpg)

### 3D View

![ATtiny412 3D](../../../images/week-6/attiny412-3d.jpg)

> Reference: [https://fabacademy.org/2026/classes/embedded_programming/index.html](https://fabacademy.org/2026/classes/embedded_programming/index.html)

---


## 📥 Installing KiCad

**[KiCad](https://www.kicad.org/)** is the open-source EDA (Electronic Design Automation) tool used across Fab Academy for schematic capture and PCB design.

1. Go to the **[official KiCad download page](https://www.kicad.org/download/)**
1. Select **Windows** and download the installer
1. Run it and go through the **KiCad Installation Manager**
1. Keep the default library selections — you can always add more later

![KiCad Download](../../../images/week-6/kicad-download.jpg)

![KiCad Download](../../../images/week-6/kicad-download-1.jpg)

![KiCad Install](../../../images/week-6/kicad-installation.jpg)

![KiCad Install](../../../images/week-6/kicad-installation-2.jpg)

![KiCad Install](../../../images/week-6/kicad-installation-3.jpg)

![KiCad Install](../../../images/week-6/kicad-installation-4.jpg)

-----

## 📚 Importing the Fab Academy KiCad Library

The standard KiCad library is great, but Fab Academy has its own library of components with footprints specifically sized and optimised for PCB milling.

You can clone the library from GitLab if you prefer:  
<https://gitlab.fabcloud.org/pub/libraries/electronics/kicad>

But the easiest way is to install it directly through KiCad's built-in plugin manager:

1. Open KiCad and go to **Plugin and Content Manager** (from the main window)
1. In the search bar, type **KiCad FabLib**
1. Select it from the results and click **Install**
1. Wait for the installation to complete and click **Apply Changes**

![KiCad Fab Library Plugin](../../../images/week-6/kicad-fab-plugin-1.jpg)

![KiCad Fab Library Plugin](../../../images/week-6/kicad-fab-plugin-2.jpg)

The Fab library is now available — you’ll see it listed as `fab` in all library searches from here on.

-----

## 🆕 Creating a New Project

1. In the KiCad project manager, click **New Project**
1. Give it a name — I called mine `gameboy less gooiii`
1. Choose a project folder and click **Save**
1. This creates a `.kicad_sch` schematic file and a `.kicad_pcb` PCB file

-----

## 📐 Building the Schematic

Double-click the **Schematic Editor** (`.kicad_sch`) to open it.

The schematic is the *logical* map of your circuit — it shows what connects to what, using standardised symbols. It doesn’t care about physical size or position yet, that comes later in the PCB editor.

### Adding Components

Press **`A`** to open the **Add Symbol** dialog, search for your component, and click to place it.

**Components I added for the NB6-Boy PCB:**

|Component                          |Symbol Source|Notes                                      |
|-----------------------------------|-------------|-------------------------------------------|
|XIAO RP2040                        |Fab Library  |Main MCU                                   |
|Push Buttons ×6                    |Fab Library  |Game controls (UP, DOWN, LEFT, RIGHT, MENU, PAUSE)|
|Speaker (LS1)                      |Fab Library  |PWM audio output                           |
|Capacitors ×2 (C_1206)             |KiCad Default|Decoupling capacitors                      |
|JST S4B-PH-SM4-TB ×4               |SnapEDA      |4-pin horizontal JST connectors (J2, J3, J9, J10)|
|JST S3B-PH-SM4-TB                  |SnapEDA      |3-pin horizontal JST connector for matrix (P1)|
|Pin Socket 01x04 (J4)              |KiCad Default|I²C breakout header                        |
|Pin Socket 01x07 ×2 (J7, J8)       |KiCad Default|GPIO expansion headers                     |

> **Note:** I used JST connectors from SnapEDA instead of the Fab Library because I needed horizontal (side-entry) connectors, and the Fab Library only has vertical ones.

### Drawing Wires

Press **`W`** to start the **Wire** tool.

- Click a pin to start the wire
- Click the destination pin to finish it
- Use **Power Symbols** (`PWR`, `GND`, `VCC`) from the Add Symbol dialog to label power nets cleanly — this avoids having to draw wires all the way across the schematic

### Why I Added Extra Connectors

I added multiple expansion connectors broken out for:

- **I²C (SDA / SCL)** — via J2, J3, J9, J10 JST connectors, so I can plug in extra I²C peripherals later (sensors, displays, etc.)
- **GPIO expansion** — via J7 and J8 pin headers for additional connections
- **Matrix connector** — P1 for the NeoPixel LED matrix

This makes the development board way more useful beyond just the NB6-Boy. If I want to use the same board for a different project down the line, those connectors are already there.

![KiCad Schematic Complete](../../../images/week-6/kicad-schematic.jpg)

-----

## ✅ Running the ERC (Electrical Rules Check)

Before moving to PCB layout, you run the **ERC** to check for any logical errors in your schematic.

1. Go to **Inspect → Electrical Rules Checker**
1. Click **Run ERC**
1. Go through the list of any errors or warnings

**Common things to fix:**

- Unconnected pins → add a `PWR_FLAG` or connect to a net
- Missing power pins → make sure all VCC and GND pins are connected
- Pin direction conflicts → double check that outputs aren’t connected to outputs

Keep fixing until it shows **0 errors, 0 warnings**.

![KiCad ERC Check](../../../images/week-6/kicad-schematic-erc.jpg)

-----

# Part 3 – Importing Components Not in the Fab Library Using SnapMagic

## 🔍 What is SnapMagic?

Sometimes the component you need — a specific display driver, a non-standard IC, a particular connector — just isn’t in the Fab library or the KiCad default library.

**[SnapMagic](https://www.snapeda.com/)** (also known as SnapEDA) is a website with a massive database of free, ready-to-use KiCad symbols, footprints, and 3D models for real electronic components. You can find almost anything there.

-----

## 📥 Downloading a Component from SnapMagic

1. Go to **[snapeda.com](https://www.snapeda.com/)**
1. In the search bar, type the exact part number (e.g. `SSD1306`, `WS2812B`, `AMS1117-3.3`)

![SnapMagic Search](../../../images/week-6/snapmagic.jpg)

1. Select the correct result from the list — double-check the package type and pin count
1. Click **Download Symbol & Footprint**
1. Choose **KiCad** from the format dropdown
1. Click **Download** — this gives you a `.zip` file

Inside the zip you’ll find:

- A `.kicad_sym` file — the schematic symbol
- A `.kicad_mod` file — the PCB footprint
- A `.step` file — a 3D model (super useful for the 3D viewer later!)

-----

## 📦 Importing into KiCad

Extract the zip somewhere sensible — I made a `custom-components/` folder inside my KiCad project folder.

### Importing the Symbol

1. In KiCad, go to **Preferences → Manage Symbol Libraries → Add Existing**
1. Navigate to the `.kicad_sym` file and select it
1. Give it a nickname like `snapmagic_custom`
1. Click **OK**

The component now shows up when you press `A` in the schematic editor — just filter by the library name you gave it.

![SnapMagic Symbol Import](../../../images/week-6/snapmagic-symbol-import.jpg)

### Importing the Footprint

1. Go to **Preferences → Manage Footprint Libraries → Add Existing**
1. Navigate to the folder containing the `.kicad_mod` file
1. Add the folder and give it a nickname
1. Click **OK**

When assigning footprints, filter by your new library name and the component will appear in the list.

### Adding the 3D Model

1. Copy the `.step` file into your project folder (e.g. inside a `3d-models/` subfolder)
1. Open the **Footprint Editor** for that component
1. Go to the **3D Models** tab
1. Click **Add** and point it to the `.step` file

Now when you open the 3D PCB viewer, the component shows as a proper 3D model instead of just a blank box — which is honestly really satisfying.

> **Important tip:** Always double-check the footprint dimensions against the component’s actual datasheet. Compare pad pitch and courtyard size carefully before you start routing — a footprint mismatch is one of the most painful mistakes to discover after fabrication.

-----

# Part 4 – PCB Layout and Routing

## 📂 Opening the PCB Editor

1. From the KiCad project manager, click the **PCB Editor** (`.kicad_pcb`)
1. Go to **Tools → Update PCB from Schematic**
1. This imports all your components as footprints and shows the **ratsnest** — the thin lines connecting pins that still need to be routed

-----

## ⚙️ Setting Design Rules

Before placing anything, set your design constraints based on what the milling machine can actually mill.

Go to **File → Board Setup → Design Rules**:

|Parameter                  |Value    |
|---------------------------|---------|
|Minimum Clearance          |0.4 mm   |
|Minimum Track Width        |0.4 mm   |
|Minimum Connection Width   |0.4 mm   |
|Minimum Annular Width      |0.275 mm |
|Minimum Via Diameter       |1.4 mm   |
|Copper to Hole Clearance   |0.25 mm  |
|Copper to Edge Clearance   |0.5 mm   |
|Minimum Through Hole       |0.85 mm  |
|Hole to Hole Clearance     |0.95 mm  |

![KiCad Design Rules](../../../images/week-6/kicad-design-rules.jpg)

-----

## 📏 Defining the Board Outline

1. Select the **Edge.Cuts** layer from the layer panel on the right
1. Use **Place → Rectangle** to draw the board outline
1. The dimensions were set to fit the available blank PCB stock in the lab — **70 mm × [height] mm**
1. Make sure it’s a complete closed loop — any gaps will cause issues later

-----

## 🧩 Placing Components

All the imported footprints start as a messy cluster outside the board boundary.

1. Click and drag each component inside the board outline
1. Press **`R`** to rotate
1. Think about the layout logically:
- MCU in the centre
- Buttons along the edges (where thumbs would naturally reach on the game console)
- Connectors at one end for easy cable access
- Passive components (capacitors, resistors) close to the relevant power pins
1. Try to minimise ratsnest line crossings before routing — the cleaner it looks now, the easier routing will be

![KiCad Component Placement](../../../images/week-6/kicad-component-placement.jpg)

-----

## 🔀 Routing Traces

1. Press **`X`** to activate the **Route Tracks** tool
1. Click a pad to start, then click the destination pad to finish the trace
1. All traces go on the **F.Cu** (front copper) layer since this is a single-sided board

**Routing order:**

- Route **power** (VCC, GND) first with wider traces (0.8 mm+) since they carry more current
- Then route **signal traces** at standard width (0.4 mm)

![KiCad Routing](../../../images/week-6/kicad-routing.jpg)

-----

## 🔍 Running the DRC (Design Rules Check)

After routing everything, run the DRC to catch any physical problems:

1. Go to **Inspect → Design Rules Checker**
1. Click **Run DRC**
1. Review any clearance violations, unrouted nets, or silkscreen overlaps

![KiCad DRC](../../../images/week-6/kicad-drc.jpg)

**About the warnings:** The warnings shown in DRC were related to **silkscreen** elements — text and labels overlapping pads or being too close to board edges. Since we're **milling our boards** in the lab, we won't have a silkscreen layer at all, so these warnings can be safely ignored.

**About the excluded errors:** Some errors flagged the **JST connectors being too close to the board edge**. These were **intentionally placed** that way — the connectors need to be at the edge so cables can plug in easily from the side of the enclosure. I reviewed these and excluded them from the error list since the placement was a deliberate design choice, not a mistake.

Another error was related to the **XIAO footprint not matching the library**. This happened because I **modified the footprint hole size from 0.8 mm to 0.85 mm** to match the drill bit available in my lab. The default 0.8 mm holes wouldn't work with our tooling, so this was a necessary adjustment — not an actual design error.

-----

# Part 5 – 3D Visualisation and Casing Design (Extra Credit)

## 🖼️ Viewing the PCB in 3D

Before doing anything else, I wanted to see what the board actually looked like physically.

1. In the PCB Editor, press **`Alt+3`** or go to **View → 3D Viewer**
1. The viewer renders all components with their assigned 3D models — including the ones imported from SnapMagic
1. Rotate and zoom to check for physical conflicts, component clearances, and overall layout quality

This is genuinely satisfying to look at after spending hours staring at 2D traces lol.

![KiCad 3D Viewer](../../../images/week-6/kicad-3dviewer.jpg)

![KiCad 3D Viewer](../../../images/week-6/kicad-3dviewer-1.jpg)

-----

## 📤 Exporting the STEP File

To use the PCB as a reference for the enclosure in Fusion 360, I exported it as a STEP file:

1. In the PCB Editor, go to **File → Export → STEP**
1. Set the output path and filename: `gameboy less gooiii.step`
1. Click **Export**

![KiCad STEP Export](../../../images/week-6/kicad-stepexport.jpg)

This generates a full 3D model of the populated PCB — components and all.

-----

## 🏠 Importing into Fusion 360 for Casing Design

1. Open **Autodesk Fusion 360**
1. Go to **File → Open → Open from my Computer**
1. Select the `gameboy less gooiii.step` file

The PCB loads as a solid body with all components in their exact positions.

### Building the Casing

1. Create a new **component** for the casing (keep it separate from the PCB body — good practice)
1. Use **Offset Plane** above the PCB surface to define the height of the enclosure walls
1. Create a **Sketch** on the XY plane and trace the board outline
1. **Extrude** the walls upward to create the bottom shell
1. Use the component positions on the PCB as guides to add cutouts:
- Cutouts for each of the 6 buttons to poke through
- A rectangular window for the OLED display
- A small hole for the buzzer
- A slot for the USB connector
1. Create the **lid** as a separate body using the same board outline
1. Apply **Fillets** to all sharp edges for better ergonomics and easier 3D printing
1. Export as `.stl` for 3D printing (that’s covered in Week 05!)

<iframe src="https://gmail1575891.autodesk360.com/shares/public/SH28cd1QT2badd0ea72beadcd9720fa787c7?mode=embed" width="100%" height="600" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" frameborder="0"></iframe>

<div style="text-align: center;">
  <video width="100%" controls>
    <source src="../../../images/week-6/gameboy.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

> This KiCad → STEP → Fusion 360 workflow is honestly one of the coolest things I’ve learned this week. Going seamlessly from a PCB layout to a mechanically accurate enclosure design, where everything fits without guesswork, is super powerful.
-----

# Part 6 – Getting Files Ready for Fabrication

Once the PCB design is complete, the next step is to export the manufacturing files. These files tell the manufacturer (or the milling machine in the lab) exactly how to produce the board.

-----

## 📤 Exporting Gerber Files from KiCad

**Gerber files** are the industry-standard format for PCB manufacturing. They contain all the layer information — copper traces, solder mask, silkscreen, drill holes, and board outline — in a format that any fabrication house can read.

### Steps to Export Gerber Files:

1. In the PCB Editor, go to **File → Fabrication Outputs → Gerbers (.gbr)**
1. In the **Plot** dialog:
   - Set the **Output Directory** — I used a `gerber/` subfolder in my project
   - Select the layers you need:
     - **F.Cu** — Front copper (your traces)
     - **B.Cu** — Back copper (if doing a 2-layer board)
     - **F.Silkscreen** — Front silkscreen labels
     - **F.Mask** — Front solder mask
     - **Edge.Cuts** — Board outline
1. Click **Plot** to generate the Gerber files

![KiCad Gerber Export](../../../images/week-6/gerber-export.jpg)

![KiCad Gerber Export](../../../images/week-6/gerber-export-1.jpg)

### Exporting the Drill File:

1. Still in the Plot dialog, click **Generate Drill Files**
2. In the **Drill File** dialog:
   - Set the same output directory as the Gerbers
3. Click **Generate Drill File**

![Generate Drill Files](../../../images/week-6/generate-drill-files.jpg)

### Packaging for Submission:

Most manufacturers expect a single `.zip` file containing all your Gerber and drill files:

1. Navigate to your `gerber/` output folder
2. Select all the generated files (`.gbr`, `.drl`, etc.)
3. Right-click and **Compress to ZIP**
4. This zip is now ready to upload to any PCB manufacturer

-----

## 🔍 Viewing Gerbers in PCBWay's Online Gerber Viewer

Before sending files off for fabrication — or even before milling in the lab — it's always a good idea to **preview your Gerber files** in a third-party viewer. This catches any export mistakes that might not be obvious in KiCad.

**[PCBWay](https://www.pcbway.com/)** has a free online Gerber viewer that's super easy to use:

### Steps to View Your Gerbers:

1. Go to [https://www.pcbway.com/project/OnlineGerberViewer.html](https://www.pcbway.com/project/OnlineGerberViewer.html)
1. Click **Add Gerber Files** or drag-and-drop your `.zip` file
1. The viewer renders your board with all layers — you can toggle each layer on/off to inspect them individually
1. Check for:
   - Any missing traces or broken connections
   - Correct board outline
   - Drill holes in the right positions
   - Silkscreen text readable and not overlapping pads

![PCBWay Gerber Viewer](../../../images/week-6/pcbway-gerber.jpg)

### Generating a Manufacturing Quote:

PCBWay also lets you get an instant quote for professional fabrication:

1. After viewing your Gerbers, click **Quote Now** or go to [https://www.pcbway.com/orderonline.aspx](https://www.pcbway.com/orderonline.aspx)
1. Upload your Gerber zip file
1. Configure your board options:
   - **Quantity** — how many boards you need
   - **Layers** — 1-layer, 2-layer, etc.
   - **Thickness** — standard is 1.6 mm
   - **Surface Finish** — HASL, ENIG, OSP, etc.
   - **Solder Mask Colour** — green, black, blue, red, etc.
1. Click **Calculate** to see the price and lead time
1. If satisfied, you can proceed to order — or just use this as a reference

![PCBWay Quote Generator](../../../images/week-6/pcbway-quoting.jpg)

> **Tip:** Even if you're milling your board in the lab, getting a quote from a manufacturer gives you a sense of what professional fabrication would cost — useful if you ever want to scale up your project.

-----

## 🖼️ Converting Gerber to PNG with Gerber2PNG (FabLab Kerala)

For Fab Academy, we often need **PNG images** of our PCB traces and outlines — especially for the upcoming **Electronics Production** week where we mill our own boards. The milling software requires high-contrast black-and-white PNG images.

**[Gerber2PNG](https://gerber2png.fablabkerala.in/)** is an awesome free tool created by **FabLab Kerala** specifically for this purpose.

### How to Use Gerber2PNG:

1. Go to [https://gerber2png.fablabkerala.in/](https://gerber2png.fablabkerala.in/)
1. Click **Choose File** or drag-and-drop your Gerber file (typically the `F.Cu` copper layer `.gbr` file)
1. The tool automatically generates a high-resolution PNG image of your traces
1. Adjust settings if needed:
   - **DPI** — higher DPI = finer detail (1000 DPI is usually good for milling)
   - **Invert** — toggle if you need white traces on black or vice versa
1. Click **Download PNG** to save the image

![Gerber2PNG Tool](../../../images/week-6/gerber-2-png.jpg)

### Files You'll Typically Convert:

|Gerber Layer|PNG Use Case|
|------------|------------|
|F.Cu (Front Copper)|Traces PNG for milling|
|Edge.Cuts|Outline/cutout PNG for cutting the board boundary|

> **Why this matters:** The mods project software we use in the lab for PCB milling requires PNG input — not Gerber. This tool bridges that gap perfectly and is a real time-saver compared to manually exporting and processing images in image editing software.

-----

# Extra Credit – Using a Different EDA Tool: EasyEDA

To try a different workflow, I also explored **[EasyEDA](https://easyeda.com/)** — a free, browser-based EDA tool that's beginner-friendly and doesn't require any software installation. It's a great alternative to KiCad for quick prototypes or simpler boards.

## Simple XIAO ESP32-C6 with RGB LED Circuit

I designed a minimal circuit featuring:

- **XIAO ESP32-C6** — the same microcontroller used in my NB6-Boy project
- **RGB LED** — a common cathode RGB LED for visual output
- **Current-limiting resistor** — to protect the LED from overcurrent

The circuit is straightforward: each colour channel of the RGB LED connects to a GPIO pin on the XIAO through a resistor, allowing independent PWM control of red, green, and blue to create any colour.

### Schematic

![EasyEDA Schematic](../../../images/week-6/easy-eda-schematic.jpg)

### PCB Layout

![EasyEDA PCB](../../../images/week-6/easy-eda-pcb.jpg)

### 3D View

![EasyEDA 3D View](../../../images/week-6/easy-eda-3d.jpg)

> EasyEDA's interface is more intuitive for beginners compared to KiCad, and the integrated parts library makes finding components quick. However, KiCad offers more control and flexibility for complex designs.

---

## Helpful Websites

- Wokwi Simulator — <https://wokwi.com/>
- Wokwi VS Code Docs — <https://docs.wokwi.com/vscode/getting-started>
- KiCad Official Site — <https://www.kicad.org/>
- Fab Academy KiCad Library — <https://gitlab.fabcloud.org/pub/libraries/electronics/kicad>
- SnapMagic (SnapEDA) — <https://www.snapeda.com/>
- PCBWay Online Gerber Viewer — <https://www.pcbway.com/project/OnlineGerberViewer.html>
- PCBWay PCB Quote — <https://www.pcbway.com/orderonline.aspx>
- Gerber2PNG (FabLab Kerala) — <https://gerber2png.fablabkerala.in/>

-----

# Reflection

Going into this week I honestly wasn’t sure how much depth there was here — I figured it was just "draw some circles and lines on a PCB." But it’s way more than that.

Understanding *why* you set clearances a certain way, *why* you route power before signal traces, *why* the ERC catches errors that your eyes would totally miss — all of that context made the process feel intentional rather than just randomly clicking around in software.

Also, designing a board that I *actually want* — one directly tied to the NB6-Boy project — made it way easier to stay motivated through the whole process.

Next up: actually fabricating this board during Electronics Production week. Cannot wait to see this thing as a physical PCB 😎

-----
---
<div style="text-align: center; margin: 40px 0; padding: 30px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); border-radius: 12px; box-shadow: 0 8px 20px rgba(0,0,0,0.15);">
  <a href="/files/week-6.rar" target="_blank" style="display: inline-block; padding: 14px 32px; background-color: white; color: #667eea; font-weight: bold; font-size: 16px; text-decoration: none; border-radius: 8px; transition: all 0.3s ease; box-shadow: 0 4px 12px rgba(0,0,0,0.15);" onmouseover="this.style.transform='translateY(-2px)'; this.style.boxShadow='0 6px 16px rgba(0,0,0,0.25);'" onmouseout="this.style.transform='translateY(0)'; this.style.boxShadow='0 4px 12px rgba(0,0,0,0.15);'">
    ⬇️ Download All Files from Week 6
  </a>
</div>

---
