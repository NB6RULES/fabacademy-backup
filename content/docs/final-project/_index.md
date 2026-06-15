+++
title = "Final Project"
weight = 200
bookCollapseSection = true
+++

# Final Project - Smart Tool Cabinet with RFID Tracking

I'm building a **Smart Tool Cabinet** that tracks tools using RFID cards for access control and mini switches in each tool slot to detect when tools are removed.

---
![Presentation slide draft](../../presentation.png)

<video controls width="100%" style="max-width: 600px; margin: 20px 0; border-radius: 6px;">
  <source src="../../presentation.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

## What It Does

- **RFID Access Control** - Each person gets an RFID card to unlock drawers they're trained to use
- **Tool Tracking** - Mini switches in each tool slot log when tools are taken and returned
- **Automatic Alerts** - System alerts if tools aren't returned on time
- **Usage Logging** - Tracks who used what and when

No more missing tools! The cabinet knows everything.

---

## Who It's For

This Smart Tool Box is designed for **anyone working in a collaborative maker space** — whether it's a Fab Lab, school workshop, university makerspace, or community workshop. It's particularly valuable for:

- **Lab Instructors and Managers:** To track tool usage, monitor availability, and maintain an organized workspace
- **Students and Makers:** To easily access tools, know when they're available, and contribute to a better-organized lab
- **Tool Owners:** To keep track of their equipment and prevent loss or misuse
- **Facility Coordinators:** To gather data on tool usage patterns and plan maintenance schedules

---

## Components

**Hardware:**
- RFID reader & cards
- Mini switch sensors (one per tool slot)
- Solenoid locks
- XIAO ESP32C6 and CH32V003J4M6 microcontrollers
- Buzzer
- Custom-fabricated enclosure

**Software:**
- RFID authentication system
- Switch monitoring & data logging
- Alert system

---

## Why This Project?

It solves a real problem (tools going missing), teaches me RFID + electronics + microcontrollers, and is actually feasible to complete. Win-win! 🚀

---

## Tools & Skills I'll Learn

✅ **RFID Technology** - I've never done this before, so that's gonna be cool to learn

✅ **Sensor Integration** - Reading multiple sensors and processing the data

✅ **Electronics & Circuits** - Wiring up solenoid locks and buzzers

✅ **Microcontroller Programming** - The actual code to make it work

✅ **3D Design & Fabrication** - Designing and fabricating the enclosure

✅ **System Integration** - Making all these different parts work together

✅ **Database/Logging** - Keeping track of all the data

---

## Timeline & Breakdown

This is lowkey a pretty big project, so I'm breaking it down:


<iframe src="https://docs.google.com/spreadsheets/d/e/2PACX-1vQd4QJIY-qwwxRDOcN8cfK8kzYhXXSCJxN_sq5hL_5EuqFRIKBJW4ukexAZ-MGphuN_HvaJz50p7CyA/pubhtml?gid=265539544&amp;single=true&amp;widget=true&amp;headers=false" width="100%" height="600" frameborder="0"></iframe>

---

## Challenges I'm Expecting

- **Power management** - All these components use power, gotta make sure it's efficient
- **Durability** - It's gonna be used a lot, so it needs to be tough
- **Cost** - All these sensors and components aren't cheap lol

But honestly, that's what makes it fun. Solving hard problems is what engineering is about!

---

## Why This Is My Final Project

At the end of the day, this project is:

✅ **Feasible** - I can actually finish it in time

✅ **Complex enough** - Uses multiple technologies and skills

✅ **Practical** - It solves a real problem that people face

✅ **Impressive** - Looks cool and works even cooler

✅ **Educational** - I'm gonna learn SO much doing this

I'm lowkey really hyped about this project. Let's get it done! 🚀

---

<a href="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/final-project/">Smart Tool Tracking Toolbox</a> © 2026 by <a href="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/">Nadec Biju</a> is licensed under <a href="https://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a><img src="https://mirrors.creativecommons.org/presskit/icons/cc.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/by.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/nc.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/sa.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;">

---

<a href="../assignment/project-development/" class="flex items-center justify-center gap-3 w-full py-4 px-6 rounded-xl font-headline font-bold text-sm uppercase tracking-widest transition-all duration-200" style="background:linear-gradient(135deg,#667eea,#764ba2); color:white; box-shadow:0 4px 20px rgba(102,126,234,0.35);" onmouseover="this.style.transform='translateY(-2px)'; this.style.boxShadow='0 8px 28px rgba(102,126,234,0.5)';" onmouseout="this.style.transform=''; this.style.boxShadow='0 4px 20px rgba(102,126,234,0.35);'">
  <span class="material-symbols-outlined" style="font-size:20px;">arrow_forward</span>
  View Project Development
</a>

<a href="../assignment/week-16/" class="flex items-center justify-center gap-3 w-full py-4 px-6 rounded-xl font-headline font-bold text-sm uppercase tracking-widest transition-all duration-200" style="background:linear-gradient(135deg,#667eea,#764ba2); color:white; box-shadow:0 4px 20px rgba(102,126,234,0.35); margin-top: 12px;" onmouseover="this.style.transform='translateY(-2px)'; this.style.boxShadow='0 8px 28px rgba(102,126,234,0.5)';" onmouseout="this.style.transform=''; this.style.boxShadow='0 4px 20px rgba(102,126,234,0.35);'">
  <span class="material-symbols-outlined" style="font-size:20px;">arrow_forward</span>
  View System Integration
</a>

