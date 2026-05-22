+++
title = "Week 18 - Applications and Implications"
weight = 118
bookCollapseSection = true
+++

# Week 18 - Applications and Implications

Week 18 focused on **applications and implications**, planning the final project in detail and considering its broader impact.  
The aim was to create a comprehensive project plan that integrates all learned skills.

This week is about strategic planning for the final project masterpiece.

---

## Assignment

### Part 1 — Plan the Final Project Masterpiece
Plan a final project **masterpiece** that integrates the range of units covered, answering:

- **What will it do?**
- **Who's done what beforehand?**
- **What sources will you use?**
- **What will you design?**
- **What materials and components will be used?**
- **Where will come from?**
- **How much will they cost?**
- **What parts and systems will be made?**
- **What processes will be used?**
- **What questions need to be answered?**
- **How will it be evaluated?**

Your project should incorporate:
- 2D and 3D design
- Additive and subtractive fabrication processes
- Electronics design and production
- Embedded microcontroller design, interfacing, and programming
- System integration and packaging

Where possible, you should **make rather than buy** the parts of your project.  
Projects can be separate or joint, but need to show **individual mastery** of the skills, and be **independently operable**.

### Part 2 — Presentation Drafts
Prepare drafts of your final project summary slide and video clip:

- **presentation.png** — 1920×1080 summary slide
- **presentation.mp4** — 1080p HTML5 video clip, < ~1 minute, < ~25 MB

Put them in your **root directory**, and check that they are linked in the final presentation schedule.

---

## Project Plan

### What will it do?

The smart toolbox keeps track of every tool inside it. Each slot has a cutout shaped for a specific hand tool or metrology instrument, and each slot has its own monitoring system — basically a **cheap microcontroller that costs around 10 cents**.

To access a tool, the person taps their RFID tag and the toolbox checks whether they have access. If they do, it unlocks and they can take the tool. The moment the tool is lifted out, the limit switch under that slot triggers, and the system logs who took what tool and when. That info gets pushed to the app so anyone can see which tools are out and who has them.

To return a tool, the person taps their RFID tag again and puts the tool back in its slot. The switch picks it up and the tool goes back into the system as available.

### Who's done what beforehand?

While scrolling through YouTube I came across [a video](https://www.youtube.com/watch?v=wOOF-MD0WIo) by a creator called **"I Like to Make Stuff"** who had built a similar tool-tracking setup. His version didn't have a toolbox — he stuck NFC tags directly onto the tools and used an RFID reader to check tools out and back in whenever he lent them to friends.

<iframe width="400" height="225" src="https://www.youtube.com/embed/wOOF-MD0WIo" title="I Like to Make Stuff — Tool tracking system" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen style="margin: 12px 0; border-radius: 6px;"></iframe>

### What sources will you use?

The project will mostly use the fabrication tools and facilities available at **Super Fab Lab Kochi**.

For fabrication, I'll be using the **ShopBot** for CNC routing, and the **Carvera** and **Roland** machines for PCB production. Final assembly is manual — hand tools and power tools.

For design and software:

- **Fusion 360** for CAD and CAM
- **KiCad** for the PCB design (open source)
- **PlatformIO** for embedded programming
- **Anthropic Claude** to help me with the Arduino firmware and the app code
- **Flutter + Android SDK + Codemagic** for building the mobile app (iOS too)

Reference docs:

- [Seeed Studio XIAO ESP32C6 — Getting Started Guide](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)

### What will you design?

- The **outer box** and drawers in Fusion 360
- The **21 PCBs** needed for the system in KiCad — 16 of them are identical (one per slot)
- The **firmware** for the microcontrollers in PlatformIO, with Claude helping me write it
- The **mobile app** in Flutter, tested through Codemagic and the Android SDK

### What materials and components will be used? / Where will they come from? / How much will they cost?

*Placeholder for Google Sheets embed*

### What parts and systems will be made?

**Physical parts**

- Outer structure
- 3 drawers in 2 different sizes
- Laser-cut back panel for electronics access
- Solenoid lock

**Electronic parts**

- Main PCB with the **XIAO ESP32C6**, the **RFID module**, and the D-in/D-out lines for the limit switch circuits

### What processes will be used?

- **ShopBot CNC routing** for the structure and drawers
- **Laser cutting** for the acrylic back panel
- **3D printing** for the solenoid lock holder
- **Electronics production** for the main PCB and breakout boards — soldering, assembly, component integration
- **Embedded programming** for the XIAO ESP32C6 handling the RFID, NeoPixels, buttons, and solenoid lock. Arduino IDE for testing.
- **Mobile app development** using Flutter, with Claude Code for the coding side and **Firebase** for the real-time database

### What questions need to be answered?

- Is the tool status being detected correctly by the switches?
- Is the data being pushed to the Firebase database in real time?
- Are the solenoid locking mechanism and RFID access system actually working?
- Can the tool status be viewed on the app?
- Can the project **successfully combine** electronics, interaction design, and fabrication into a **cohesive working system**?

### How will it be evaluated?

By testing:

- Tool status tracking
- Communication between nodes (switches)
- Solenoid locking mechanism
- NeoPixel lighting
- RFID access control
- App refreshing with live data

**System integration** — checking whether the mechanical systems, electronics, embedded programming, and mobile app all work together as one cohesive system.

**Fabrication quality** — evaluating structure assembly, component placement, durability of moving parts, and accessibility for maintenance.

---

## Assignment II — Preparing the Presentation Draft

### Slide Draft

For the slide I just opened up **Google Slides**, set the canvas to **1920×1080**, and put together a quick draft — title, subtitle, logos, and placeholders for the images I'll swap in later. Exported it as `presentation.png`, dropped it into the `public` folder, and committed it.

![Presentation slide draft](../../../presentation.png)

### Video Draft

For the video I went straight to **CapCut** on my phone — way easier than fighting a desktop editor for something this short. Trimmed clips, arranged the sequence, fixed orientation, and sorted out resolution all from mobile.

![CapCut mobile editing](../../../images/week-18/capcut.jpg)

Once the edit looked decent, I exported it at **1080p** and moved the file over to my PC for compression.

Compression was handled by **HandBrake**. I imported the preset file Fab Academy provides for the presentation video requirements, saved it as a custom preset, and exported using those settings. The file size dropped a lot without the video looking awful — which is basically the whole point for web submission.

![HandBrake preset import](../../../images/week-18/handbrake-1.jpg)

![HandBrake export settings](../../../images/week-18/handbrake-2.jpg)

Renamed the output to `presentation.mp4` and dropped it into the `public` folder of the repo.

<video controls width="100%" style="max-width: 600px; margin: 20px 0; border-radius: 6px;">
  <source src="../../../presentation.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

After pushing both files, I jumped over to the **Fab Academy Final Project Schedule** page and checked that the slide and video were correctly linked under my entry. They were. ✅

![Fab Academy Final Project Schedule page](../../../images/week-18/fabacademy-schedule.jpg)

> **🎬 Video clip sources**
>
> - [Shutterstock — cat meme search](https://www.shutterstock.com/video/search/cat-meme)
> - [Shutterstock clip #3951217585](https://www.shutterstock.com/shutterstock/videos/3951217585/thumb/1.jpg?ip=x480)
> - [Shutterstock clip #3997653259](https://www.shutterstock.com/shutterstock/videos/3997653259/thumb/1.jpg?ip=x480)
> - [Pinterest reference](https://in.pinterest.com/pin/51861833202289212/)
> - [YouTube reference](https://www.youtube.com/watch?v=Iqmufn07R28)

---

