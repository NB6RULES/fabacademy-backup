+++
title = "Final Project"
weight = 200
bookCollapseSection = true
+++

# Final Project - Smart Tool Cabinet with RFID Tracking

I build a **Smart Tool Cabinet** that tracks tools using RFID cards for access control and mini switches with individual microcontrollers in each tool slot to detect when tools are removed.

---

## Presentation Slides
![Presentation slide draft](../../presentation.png)


## Presentation Video
<video controls width="100%" style="margin: 20px 0; border-radius: 6px;">
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
- Custom-fabricated enclosure

**Software:**
- RFID authentication system
- Switch monitoring & data logging
- Alert system
- Mobile App (IOS and Android) for notifications and tool status

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

---

<a href="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/final-project/">Smart Tool Tracking Toolbox</a> © 2026 by <a href="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/">Nadec Biju</a> is licensed under <a href="https://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a><img src="https://mirrors.creativecommons.org/presskit/icons/cc.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/by.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/nc.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;"><img src="https://mirrors.creativecommons.org/presskit/icons/sa.svg" alt="" style="display: inline-block; vertical-align: middle; max-width: 1em; max-height: 1em; margin-left: .2em;">

---

<div class="related-links-grid">
  <a href="../assignment/project-development/" class="related-link-card">
    <div class="related-link-square">
      <div class="image-area">
        <img src="/images/week-20/project-development.jpg" alt="Project Development" class="card-image" onerror="this.style.display='none'; this.nextElementSibling.style.display='block';">
        <svg class="placeholder-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><rect x="3" y="3" width="18" height="18" rx="2" ry="2"></rect><circle cx="8.5" cy="8.5" r="1.5"></circle><polyline points="21 15 16 10 5 21"></polyline></svg>
      </div>
    </div>
    <span class="related-link-label">Project Development</span>
  </a>

  <a href="../assignment/week-16/" class="related-link-card">
    <div class="related-link-square">
      <div class="image-area">
        <img src="/images/week-16/week-16.jpg" alt="System Integration" class="card-image" onerror="this.style.display='none'; this.nextElementSibling.style.display='block';">
        <svg class="placeholder-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><rect x="3" y="3" width="18" height="18" rx="2" ry="2"></rect><circle cx="8.5" cy="8.5" r="1.5"></circle><polyline points="21 15 16 10 5 21"></polyline></svg>
      </div>
    </div>
    <span class="related-link-label">System Integration</span>
  </a>

  <a href="../assignment/week-18/" class="related-link-card">
    <div class="related-link-square">
      <div class="image-area">
        <img src="/images/week-18/week-18.jpg" alt="Applications and Implications" class="card-image" onerror="this.style.display='none'; this.nextElementSibling.style.display='block';">
        <svg class="placeholder-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><rect x="3" y="3" width="18" height="18" rx="2" ry="2"></rect><circle cx="8.5" cy="8.5" r="1.5"></circle><polyline points="21 15 16 10 5 21"></polyline></svg>
      </div>
    </div>
    <span class="related-link-label">Applications and Implications</span>
  </a>
</div>

{{< zipdownload dir="week-20" label="Download All The Files For Building This Project" >}}


<style>
.related-links-grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 20px;
  margin: 40px 0;
}

.related-link-card {
  text-decoration: none;
  transition: transform 0.3s ease, box-shadow 0.3s ease;
  cursor: pointer;
  display: block;
}

.related-link-card:hover {
  transform: translateY(-8px);
}

.related-link-square {
  aspect-ratio: 1;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border-radius: 12px;
  position: relative;
  overflow: hidden;
  box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
  transition: all 0.3s ease;
}

.related-link-card:hover .related-link-square {
  box-shadow: 0 8px 25px rgba(102, 126, 234, 0.4);
}

.related-link-square .card-image {
  position: absolute;
  inset: 0;
  width: 100%;
  height: 100%;
  object-fit: cover;
  display: block;
  z-index: 2;
  margin: 0 !important;
  border: none !important;
  border-radius: 0 !important;
}

.related-link-square .image-area {
  position: absolute;
  inset: 0;
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 1;
}

.related-link-square .placeholder-icon {
  width: 50px;
  height: 50px;
  color: rgba(255, 255, 255, 0.5);
  opacity: 0.6;
}

.related-link-label {
  display: block;
  margin-top: 10px;
  color: var(--body-color, inherit);
  font-weight: 700;
  font-size: 1em;
  text-align: center;
}

@media (max-width: 768px) {
  .related-links-grid {
    grid-template-columns: repeat(2, 1fr);
    gap: 15px;
  }
}

@media (max-width: 480px) {
  .related-links-grid {
    grid-template-columns: 1fr;
    gap: 12px;
  }
}
</style>

