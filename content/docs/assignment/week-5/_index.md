+++
title = "Week 05 - 3D Scanning and Printing"
weight = 105
bookCollapseSection = true
+++

# Week 05 - 3D Scanning and Printing

Week 5 focused on **3D scanning and printing**, exploring additive manufacturing technologies and reverse engineering objects through scanning.  
The aim was to understand design rules for 3D printing, test printer capabilities, and explore 3D scanning workflows.

This week continued the digital fabrication journey, adding additive manufacturing to the subtractive processes learned earlier.

---

## Group Assignment
- Test the **design rules** for your 3D printers
- Characterize your printer(s):
  - Dimensions
  - Tolerances
  - Surface quality
  - Support requirements

## Individual Assignment
- Design and 3D print an object that **could not be easily made subtractively**
- 3D scan an object, try to prepare it for printing

**Extra Credit Goals**
- Try **different printing processes**
- Try **different scanning processes**

---

## Software Used
- **CAD Software** for designing 3D printable objects - I used **SolidWorks** for the lattice structure and **Fusion 360** for the engine model.
- **Slicer Software** for preparing prints - I used **Bambu Studio** for slicing and generating G-code.
- **3D Scanning Software** for capturing and processing scans - I used the **Artec Studio** software for processing the Artec Leo scans and the **Kiri Engine** app for photogrammetry and Iphone Lidar Scan.
- **Browser + Git** for documentation

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on 3D scanning and printing |
| THU | Group Assignment - Bambu A1, Prusa XL, Bambu X1C, Formlabs |
| FRI | Introduction To 3D Scanning |
| SAT | Designing For 3d Printing |
| SUN | Continuation of design work |
| MON | 3d Scanning and post processing |
| TUE | Regional review |

---
# Week 05 – 3D Printing and Scanning

The assignment for this week was to:

- **Design, document, and 3D print an object that could not be made subtractively**
- **3D scan an object and optionally 3D print it**

---

## Group Assignment  
🔗 https://fabacademy.org/2026/labs/kochi/group_assignmetns/week05/

### Overview

As part of the group assignment, we focused on **understanding the design rules and physical limitations of our 3D printers** by printing and analyzing test geometries.

The goal was to experimentally determine:

- Maximum **bridging length**
- Maximum **overhang angle without supports**
- Minimum **clearance between moving parts**
- Wall thickness limits
- Dimensional accuracy

### Observations and Learnings

![Group Assignment Test 1](/images/week-5/group-1.jpg)
![Group Assignment Test 2](/images/week-5/group-2.jpg)
- **Bridging:**  
  The printer was able to handle bridges up to ~20 mm effectively. Beyond this, sagging and stringing began to occur.

- **Overhangs:**  
  Angles up to **45°** printed cleanly without supports. Angles beyond this required support structures for good surface quality.

- **Clearances:**  
  Small gaps are critical for moving parts. Insufficient clearance leads to fused components. Generally keep the **clearance greater than 0.3mm** for PLA.

- **Supports and Orientation:**  
  Print orientation plays a major role in reducing the need for supports and improving surface finish.

### Importance

This testing directly influenced my individual designs, ensuring:

- No unnecessary supports
- Better print quality
- Functional print-in-place mechanisms

---

## Subtractive vs Additive Manufacturing

![Subtractive vs Additive Manufacturing](/images/week-5/manufacturing-1.jpg) 
img source : https://www.radsourcing.com/blog/additive-and-subtractive-manufacturing/


| Subtractive Manufacturing | Additive Manufacturing |
|---------------------------|------------------------|
| Material is removed from a block | Material is added layer by layer |
| Examples: CNC, milling, turning | Example: FDM 3D printing |
| Limited by tool accessibility | Can create internal geometries |
| Generates material waste | Minimal waste |
| Requires multiple setups for complex parts | Can produce complex parts in one go |

### Key Insight

Additive manufacturing enables:

- Internal cavities
- Lattice structures
- Print-in-place assemblies

These are **impossible or extremely difficult** using subtractive methods.

---

# Individual Assignment

## Machine and Material

I used my personal **Bambu Lab A1** 3D printer along with **WOL3D PLA filament**.
https://bambulab.com/en-in/a1


### Filament Specifications
https://wol3d.com/product/pla-black-3/
- Print Temperature: **190°C – 220°C**
- Bed Temperature: **50–60°C**
- Shrinkage / Warping: Minimal
- Diameter: **1.75 mm**

Since I am very familiar with both the printer and filament, the process was smooth. I used the **default Generic PLA settings** in Bambu Studio.

---

# Items Designed and Printed

I designed and 3D printed **three items**.

---

## Item 1 – 3D Octagonal Lattice Structure

### Design Process

- Opened **SolidWorks**
- Created a **single octagonal unit cell**

![SolidWorks Octagonal Unit Cell](/images/week-5/solid-1.jpg)

- Used **linear patterning in assembly** to form the full lattice

![SolidWorks Linear Patterned Assembly](/images/week-5/solid-2.jpg)

### Design Considerations

From group assignment results:

- **Bridge lengths < 20 mm**
- **Overhang angles < 45°**

#### Bridging (Detailed)

Bridging occurs when filament is extruded across a gap with no support.

- If too long → filament sags due to gravity  
- Keeping it under 20 mm ensures:
  - Clean spans  
  - Minimal drooping  
  - Structural integrity  

#### Overhangs (Detailed)

Overhang angle determines how much of a layer is supported.

- Below 45° → each layer is supported by the previous one  
- Above 45° → material prints into air → poor finish  

By keeping within limits:
- No supports required  
- Faster print  
- Cleaner output  

### Printing Process

- Imported into **Bambu Studio**
https://bambulab.com/en-in/download/studio
- Arranged model on build plate
![Lattice on Build Plate 1](/images/week-5/lattice-01.jpg)
- Sliced using:
  - **0.2 mm layer height**
  - **No supports**
- Sent to printer via **Print Plate**
![Lattice Build Plate Setup](/images/week-5/lattice-02.jpg)
- Print started

### Hero Shots
![Lattice Printing 1](/images/week-5/lattice-03.jpg)
![Lattice Printing 2](/images/week-5/lattice-04.jpg)
![Lattice Final Result 1](/images/week-5/lattice-1.jpg)
![Lattice Final Result 2](/images/week-5/lattice-2.jpg)


---

## Item 2 – Goblin Flexi Toy

While scrolling through Instagram, I came across:

🔗 https://www.instagram.com/piodeer.stl/

They had posted a reel on making a **flexi toy**, which inspired me.

I decided to convert the **Goblin model I created in Week 2 (Blender)** into a flexi toy.

🔗 [View Goblin Model Creation in Week 2](../week-2/#blender-sculpting-where-it-got-fun)

### Process

- Contacted the creator and obtained a cutter file
- Discussed with instructor **[Saheen](https://fabacademy.org/2021/labs/kochi/students/saheem-palayi/)**
- Was instructed to **design my own cutter**

### Design Workflow

- Studied the reference cutter
- Designed my own version from scratch
- Imported both files into **Bambu Studio**:
  - Goblin → **Positive body**
  ![Goblin Model 1](/images/week-5/goblin-1.jpg)

  - Cutter → **Negative body**
![Goblin Model 2](/images/week-5/goblin-2.jpg)
![Goblin Model 3](/images/week-5/goblin-3.jpg)
![Goblin Model 4](/images/week-5/goblin-4.jpg)
![Goblin Model 5](/images/week-5/goblin-5.jpg)
![Goblin Model 6](/images/week-5/goblin-6.jpg)
- Performed boolean merge

### Printing Process

- Sliced the model
- Selected **Print Plate**
- Sent to printer
- Print started

### Hero Shots
![Goblin Printing 1](/images/week-5/goblin-7.jpg)
![Goblin Printing 2](/images/week-5/goblin-8.jpg)
![Goblin Printing 3](/images/week-5/goblin-9.jpg)
![Goblin Printing 4](/images/week-5/goblin-10.jpg)
---

## Item 3 – Print-in-Place Engine Model

I was asked by **[Saheen](https://fabacademy.org/2021/labs/kochi/students/saheem-palayi/)** to design something that combines:

- **Clearances**
- **Bridging**
- **Print-in-place functionality**

### Concept

Initially planned a car, but instead designed a **simple engine model** with:

- Crankshaft  
- Piston  
- Connecting rod  
- Casing  

### Design Process

- Used **Fusion 360 (hybrid modeling)**
- Created multiple interacting components
- Ensured all parts are printable as a single assembly

<video autoplay loop muted controls width="400" style="border-radius: 8px; max-width: 100%; display: block; margin: 0 auto;">
  <source src="/images/week-5/Engine-1.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

### Key Considerations

- **Clearances:** Prevent fusion of moving parts  
- **Bridging:** Maintain unsupported spans within limits  
- **Assembly-free:** Fully print-in-place  

### Printing Process

- Imported into **Bambu Studio**
- Arranged on plate
- Sliced with:
  - **0.2 mm layer height**
  - **tree supports**
- Sent to printer and printed
![Engine Printing 1](/images/week-5/engine-01.jpg)
![Engine Printing 2](/images/week-5/engine-02.jpg)

### Hero Shots

![Engine Hero Shot 1](/images/week-5/engine-2.jpg)
![Engine Hero Shot 2](/images/week-5/engine-3.jpg)

<video autoplay loop muted controls width="400" style="border-radius: 8px; max-width: 100%; display: block; margin: 0 auto;">
  <source src="/images/week-5/Engine-4.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

## Conclusion (3D Printing)

This completes my three designed prints:

1. Lattice structure  
2. Flexi goblin toy  
3. Print-in-place engine  

Each demonstrates different strengths of additive manufacturing.

---

## Why These Designs Cannot Be Made Subtractively

### Item 1 – Octagonal Lattice Structure

**Why subtractive doesn't work:**
- Has **hollow sections inside** that can't be reached by cutting tools
- Making it with subtractive methods would waste ~90% of the material
- Multiple cuts would weaken the connections between lattice pieces

**Why 3D printing works:**
- Builds the structure layer-by-layer with hollow spaces already in place
- No material waste
- All connections stay strong

---

### Item 2 – Goblin Flexi Toy

**Why subtractive doesn't work:**
- Needs **thin, flexible walls** that would break during cutting
- Requires precise channels for movement—hard to cut without damaging the model
- All the articulation channels need to be part of one piece

**Why 3D printing works:**
- Prints as one complete piece with all flex channels built in
- The walls stay intact during printing
- Flexible right after printing

---

### Item 3 – Print-in-Place Engine Model

**Why subtractive doesn't work:**
- Has **moving parts inside** (crankshaft, piston) that need to work together
- Can't mill all parts together—each piece would need to be made separately and then assembled
- Hard to get exact clearances between moving parts when assembling by hand

**Why 3D printing works:**
- Prints as one complete assembly with everything in the right place
- Clearances are already built into the design
- Engine works immediately after printing—no assembly needed

---

# Failures and Learnings

Coming to the most important part of my 3D printing week — **failures and what I learned from them**.

Most of the issues I faced were during the **engine model print**, which involved complex geometry, clearances, and print-in-place mechanisms.

---

## Failure 1 – Power Failure During Print

During one of the prints, there was a **power cut**, and although the printer resumed the job, it resulted in a visible defect.

### Issue

- The print resumed after interruption  
- The layer at the restart point **did not adhere properly**  
- A clear layer line / weak interface was visible  

![Power Failure Print Defect](/images/week-5/fail-1.jpg)

### Why This Happened

- The previously printed layer had **cooled down**
- When printing resumed:
  - Poor interlayer bonding occurred  
  - Slight misalignment may have been introduced  
- Resulted in:
  - Weak structural region  
  - Visible surface defect  

### Learning

- Power interruptions can significantly affect print integrity  
- Critical prints should ideally:
  - Be done with **stable power**
  - Or use **power backup systems (UPS)**  

---

## Failure 2 – Improper Support at Crankshaft

Another major issue occurred at the **crankshaft region** of the engine model.

### Issue

- Insufficient support under certain features  
- Resulted in:
  - Sagging  
  - Deformation  
  - Poor surface finish  

![Crankshaft Sagging 1](/images/week-5/fail-2.jpg)
![Crankshaft Sagging 2](/images/week-5/fail-3.jpg)

<video autoplay loop muted controls width="400" style="border-radius: 8px; max-width: 100%; display: block; margin: 0 auto;">
  <source src="/images/week-5/Fail-4.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>  

### Why This Happened

- Some areas exceeded:
  - Safe overhang limits  
  - Safe bridging limits  
- Lack of support led to:
  - Unsupported extrusion  
  - Gravity-induced deformation  

### Learning

- Even when designing for **no supports**, careful inspection is needed  
- Important to:
  - Analyze model orientation  
  - Identify hidden overhangs  
  - Balance between design constraints and printability  

---

## Key Takeaways

- Real-world printing is not just about design — **execution matters equally**
- Failures provided deeper insights into:
  - Material behavior  
  - Machine limitations  
  - Design-for-print principles  

These failures helped refine my understanding of:

- Bridging limits  
- Overhang handling  
- Importance of print stability  

---

Overall, these mistakes were extremely valuable and helped me improve both my **design approach** and **printing strategy** for future projects.
# 3D Scanning

I explored **two different workflows**:

---

## Workflow 1 – Artec Leo Scanner
https://www.artec3d.com/portable-3d-scanners/artec-leo/

1. Turned on the **Artec Leo scanner**
2. Selected **New Project**
3. Adjusted distance to avoid background capture
4. Started scanning
![Artec Scan 1](/images/week-5/scan-1.jpg)
![Artec Scan 2](/images/week-5/scan-2.jpg)
![Artec Scan 3](/images/week-5/scan-3.jpg)
![Artec Scan 4](/images/week-5/scan-4.jpg)
5. Completed scan
6. Exported to **Artec Studio** for post-processing https://www.artec3d.com/3d-software/artec-studio
![Artec Studio Post-processing](/images/week-5/artec-1.jpg)
### Object Scanned

- Stool
  <div class="sketchfab-embed-wrapper" style="width: 100%; max-width: 640px; margin: 0 auto; overflow: hidden;"> <iframe title="Nadec Scan" frameborder="0" allowfullscreen mozallowfullscreen="true" webkitallowfullscreen="true" allow="autoplay; fullscreen; xr-spatial-tracking" xr-spatial-tracking execution-while-out-of-viewport execution-while-not-rendered web-share width="100%" height="480" src="https://sketchfab.com/models/799ed281345940fe970192ee38c58666/embed"> </iframe> <p style="font-size: 13px; font-weight: normal; margin: 5px; color: #4A4A4A;"> <a href="https://sketchfab.com/3d-models/nadec-scan-799ed281345940fe970192ee38c58666?utm_medium=embed&utm_campaign=share-popup&utm_content=799ed281345940fe970192ee38c58666" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> Nadec Scan </a> by <a href="https://sketchfab.com/Nb6_rules?utm_medium=embed&utm_campaign=share-popup&utm_content=799ed281345940fe970192ee38c58666" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> Nb6_rules </a> on <a href="https://sketchfab.com?utm_medium=embed&utm_campaign=share-popup&utm_content=799ed281345940fe970192ee38c58666" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;">Sketchfab</a></p></div>

### Status

- Scan complete  
- Post-processing pending  

---

## Workflow 2 – Kiri Engine (Mobile)

### Process

1. Opened the app 
2. Selected **New Project**
<img src="/images/week-5/scan-5.jpg" height="300px" alt="Kiri Engine App Screenshot 1">
3. Selected **LiDAR Scan**  
<img src="/images/week-5/scan-6.jpg" height="300px" alt="Kiri Engine LiDAR Selection">
4. Selected **Object Scan**  
<img src="/images/week-5/scan-7.jpg" height="300px" alt="Kiri Engine Object Scan">
5. Followed on-screen instructions  
<img src="/images/week-5/scan-8.jpg" height="300px" alt="Kiri Engine Scan Process 1">
<img src="/images/week-5/scan-9.jpg" height="300px" alt="Kiri Engine Scan Process 2">
<img src="/images/week-5/scan-10.jpg" height="300px" alt="Kiri Engine Scan Process 3">
6. Completed scan

### Object / People Scanned

- My classmate **Merin** https://fabacademy.org/2026/labs/kochi/students/merin-cyriac/

  ![Merin 3D Scan](/images/week-5/merin.jpg)

  <div class="sketchfab-embed-wrapper" style="width: 100%; max-width: 640px; margin: 0 auto; overflow: hidden;"> <iframe title="3D Model" frameborder="0" allowfullscreen mozallowfullscreen="true" webkitallowfullscreen="true" allow="autoplay; fullscreen; xr-spatial-tracking" xr-spatial-tracking execution-while-out-of-viewport execution-while-not-rendered web-share width="100%" height="480" src="https://sketchfab.com/models/c17980cee5794a2fad8e2c428ee8b295/embed"> </iframe> <p style="font-size: 13px; font-weight: normal; margin: 5px; color: #4A4A4A;"> <a href="https://sketchfab.com/3d-models/3d-model-c17980cee5794a2fad8e2c428ee8b295?utm_medium=embed&utm_campaign=share-popup&utm_content=c17980cee5794a2fad8e2c428ee8b295" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> 3D Model </a> by <a href="https://sketchfab.com/Nb6_rules?utm_medium=embed&utm_campaign=share-popup&utm_content=c17980cee5794a2fad8e2c428ee8b295" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> Nb6_rules </a> on <a href="https://sketchfab.com?utm_medium=embed&utm_campaign=share-popup&utm_content=c17980cee5794a2fad8e2c428ee8b295" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;">Sketchfab</a></p></div>

  3d printed model of Merin
  ![Merin 3D Print](/images/week-5/merin-3dprint.jpg)


- My Gaming Handheld Device from Week 4
  <div class="sketchfab-embed-wrapper" style="width: 100%; max-width: 640px; margin: 0 auto; overflow: hidden;"> <iframe title="3D Model" frameborder="0" allowfullscreen mozallowfullscreen="true" webkitallowfullscreen="true" allow="autoplay; fullscreen; xr-spatial-tracking" xr-spatial-tracking execution-while-out-of-viewport execution-while-not-rendered web-share width="100%" height="480" src="https://sketchfab.com/models/ae733527d27c41fa8acda239564dcbf8/embed"> </iframe> <p style="font-size: 13px; font-weight: normal; margin: 5px; color: #4A4A4A;"> <a href="https://sketchfab.com/3d-models/3d-model-ae733527d27c41fa8acda239564dcbf8?utm_medium=embed&utm_campaign=share-popup&utm_content=ae733527d27c41fa8acda239564dcbf8" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> 3D Model </a> by <a href="https://sketchfab.com/Nb6_rules?utm_medium=embed&utm_campaign=share-popup&utm_content=ae733527d27c41fa8acda239564dcbf8" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;"> Nb6_rules </a> on <a href="https://sketchfab.com?utm_medium=embed&utm_campaign=share-popup&utm_content=ae733527d27c41fa8acda239564dcbf8" target="_blank" rel="nofollow" style="font-weight: bold; color: #1CAAD9;">Sketchfab</a></p></div>

### Next Plan

- Clean the mesh  
- Fix artifacts  
- **3D print a scaled model**

---

## Reflection

This week felt like a shift from just designing things to actually *manufacturing intelligently*.

Coming from a strong CAD background, I initially thought this week would be easy — but I quickly realized that 3D printing introduces a completely new layer of complexity. A model that looks perfect in CAD can completely fail during printing if design rules and machine limitations are not considered.

What stood out to me the most was how **real-world constraints dominate the outcome**:
- orientation affects strength and surface finish  
- supports affect both print success and post-processing  
- small parameter changes can completely change the result  

3D scanning was also an eye-opener. I expected clean models directly, but in reality, the process is messy and requires multiple iterations and cleanup. It made me appreciate how imperfect real-world data is compared to CAD models.

One thing I did well this week was experimenting beyond just the assignment. Instead of making something basic, I explored workflows and pushed towards more interesting outputs, which aligns more with how I like to work.

If I had more time, I would:
- experiment more with different materials (PLA, PETG, etc.)
- optimize prints for strength vs speed
- explore higher-quality scanning workflows (LiDAR vs photogrammetry)

Overall, this week strengthened my understanding that:
> Designing is only half the job — manufacturing constraints define the final result.

This directly connects to my long-term goal of building automated fabrication workflows, where design → slicing → printing can be streamlined with minimal manual intervention.

---  