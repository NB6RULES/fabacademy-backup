+++
title = "Week 07 - Computer Controlled Machining"
weight = 107
bookCollapseSection = true
+++

# Week 07 - Computer Controlled Machining

Week 7 is all about **Computer Controlled Machining** — this is the week where we go big. Literally. The brief is to design and fabricate a **meter-scale object** from sheet material using a CNC router. No more laser-cut cardboard prototypes, this time we're cutting full sheets of plywood on a ShopBot.

I used this week as an opportunity to design something I actually wanted — a **Lazy Boy–style recliner chair** driven by a four-bar linkage mechanism. Mechanical engineering background finally coming in handy 😎

---

## Group Assignment
- Do your lab's **safety training**
- Test **runout, alignment, fixturing, speeds, feeds, materials, and toolpaths** for your machine

## Individual Assignment
- Make (design + mill + assemble) something **big** (~meter-scale)

**Extra Credit Goals**
- Don't use **fasteners or glue**
- Include **curved surfaces**
- Use **three-axis toolpaths**

---

## What I Learned

This week gave me a proper end-to-end understanding of the CNC machining workflow — from theory all the way through to a finished, sanded, assembled object.

Key things I picked up:

- How CNC milling parameters (feed rate, step-over, spindle speed) affect cut quality and material
- How to design a four-bar linkage using a custom HTML simulator I built with Claude
- Why parametric design in Fusion 360 + the Arrange feature makes CNC iteration dramatically faster
- How press-fit tolerances translate from a test gauge into a real assembly
- How to set up VCarve Pro toolpaths and send them to the ShopBot
- Post-processing techniques: tab removal, sanding, and edge filleting with a wood router

---

## Software Used

- **Fusion 360** — parametric CAD modeling and part arrangement for DXF export
- **VCarve Pro** — CAM toolpath generation for the ShopBot
- **Claude (AI)** — HTML four-bar linkage simulator for determining link lengths
- **CATIA** — ergonomic analysis (RULA & REBA)
- **Inkscape** — opening and preparing DXF files for laser cutter prototype
- **ShopBot Software** — machine control and file sending

---

## Tools Used

| Tool | Purpose |
|------|---------|
| Cordless drill | Screwing the plywood to the CNC bed |
| Screws | Securing plywood to the  |
| Mallet | Assembling press-fit joints |
| Chisel | Removing tabs and cleaning edges |
| Hammer | General assembly work |
| Sandpaper (80 grit) | Rough sanding and smoothing surfaces |
| Rasp file | Shaping and removing material from edges |
| Half-round file | Smoothing curved surfaces and slots |
| Reciprocating sander | Faster surface finishing |
| Wood router | Edge filleting and chamfering |
| F-clamp | Holding pieces during assembly and gluing |

---


## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on computer-controlled machining |
| THU | Group Assignment |
| FRI | Design of the chair |
| SAT |  Rula and Reba analysis and testing out by cutting the deign in cardboard |
| SUN | Cnc Milling the Plywood and post processing |
| MON | Assembly of the chair|
| TUE | Regional review |

---

## Group Assignment – CNC Test Gauge

For the group assignment, we designed and milled a **runoff test gauge** to characterise the ShopBot's capabilities and determine the correct press-fit tolerances for our plywood stock.

### Understanding the ShopBot

![ShopBot CNC router in the lab](../../../images/week-7/shopbot-1.jpg)

Our instructors **[Mr. Mufeed](https://fabacademy.org/2023/labs/kochi/students/mufeed-mohamed/)** and **[Mr. Ravishankar](https://fabacademy.org/2025/labs/kochi/students/revisankar-s/about.html)** introduced us to the ShopBot CNC router available in our lab. The machine has a bed size of **8 feet × 4 feet**, which is large enough to mill full standard sheets of plywood in a single setup.

Before touching the machine, we went through the necessary safety briefing.

![Safety briefing session before using the ShopBot](../../../images/week-7/safety-briefing.jpg)

**PPE required at all times while the machine is running:**

| Equipment | Purpose |
| --- | --- |
| Safety goggles | Eye protection from flying chips and debris |
| Dust mask / respirator | Prevents inhalation of wood dust and fine particles |
| Ear protection | The spindle and vacuum extraction system generate continuous high noise levels |

**Clothing rules:**
- No loose clothing — can get caught in moving parts
- Long hair must be tied back
- No watches, bracelets, bangles, or dangling accessories

![Safety PPE — goggles, mask, ear protection](../../../images/week-7/ppe.jpg)

---


### Press-fit tolerance result:
 The optimal slot width for a snug press-fit with our plywood was determined to be **0.1 mm** — slightly less than the nominal material thickness to account for the machine's tolerance and any material variation.

![pressfit-tolerance-result](../../../images/week-7/group-1.jpg)

> Check out the full group documentation for all the test results and measurements:
> 🔗 https://fabacademy.org/2026/labs/kochi/group_assignmetns/week07/

---

# Part 1 – Concept and Mechanism Design

## 💡 The Idea: A Lazy Boy Recliner

For the individual assignment, I wanted to make something that was actually useful — not just a stool or a shelf like you see in a lot of CNC week projects. Since I'm a big fan of lying down , I decided to design a **Lazy Boy–style recliner chair**.

The challenge: most commercial recliners use pre-built metal mechanisms that are designed for mass manufacturing, not CNC fabrication from sheet material. I needed a simpler mechanical approach that I could actually mill and assemble.

![Reference image of a Lazy Boy recliner chair](../../../images/week-7/recliner.jpg)

---

## ⚙️ The Four-Bar Linkage Solution

After thinking about it for a while, I realized the reclining motion could be replicated using a **four-bar linkage** — a classic mechanism I'd studied during my mechanical engineering coursework.

A four-bar linkage consists of four rigid links connected by pivot joints. By choosing the right link lengths, you can control the path and angle that any point on the mechanism follows — which is exactly what you need to make a seat recline smoothly while also adjusting the footrest.

![Four-bar linkage diagram — showing the four links and pivot joints](../../../images/week-7/four-bar-diagram.jpg)

### 📚 Resources for Manual Calculation

If you want to understand the underlying math behind four-bar linkage analysis (position, velocity, acceleration), these resources are excellent references:

- 🔗 [Four-Bar Linkage Tutorial – Alistair's Tutorials](https://alistairstutorials.co.uk/tutorial30.html) — interactive walkthrough of the geometry and equations
- 🔗 [Four-bar Linkage Analysis (PDF) – Mechanical Design 101](https://mechanicaldesign101.com/wp-content/uploads/2017/12/T1-Four-bar-Linkage-Analysis-revised.pdf) — detailed mathematical derivations for position analysis

---

## 🤖 Building a Simulator with Claude

Manually calculating the correct link lengths for the desired motion would involve a lot of iterative trial-and-error math. I first tried setting up the simulation in **Desmos**, but it quickly got cumbersome with the nested equations involved.

<iframe src="https://www.desmos.com/calculator/egmi3wr0o7" width="100%" height="500" style="border: 1px solid #ccc; border-radius: 8px;" frameborder="0"></iframe>

Instead, I used **Claude** (the AI assistant) — I described my design requirements: the range of motion, the seat-to-ground angle constraints, the footrest travel arc. Claude generated a clean **HTML-based four-bar linkage simulator** that let me drag sliders to adjust each link length and see the resulting motion in real time.

<iframe src="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/week-7/chair-4-bar-linkage-calculator/" width="100%" height="600" style="border: 1px solid #ccc; border-radius: 8px;" frameborder="0"></iframe>

<div style="text-align: center; margin: 20px 0;">
  <a href="https://fabacademy.org/2026/labs/kochi/students/nadec-biju/docs/assignment/week-7/chair-4-bar-linkage-calculator/" target="_blank" style="display: inline-block; padding: 12px 24px; background-color: #667eea; color: white; font-weight: bold; text-decoration: none; border-radius: 8px; transition: all 0.3s ease;" onmouseover="this.style.backgroundColor='#764ba2';" onmouseout="this.style.backgroundColor='#667eea';">
    🔗 Open Simulator in New Tab
  </a>
</div>

This tool was a huge time-saver — within 15 minutes ( wouldve taken 3-4 hpurs manually calculating or creating an excel sheet for the calculation ) I had the correct link lengths for both the seat mechanism and the footrest linkage.

**Final link lengths determined from the simulator:**

| Link | Length (mm) | Description |
| --- | --- | --- |
| L1 Ground (A→D) | 471 mm | Fixed base distance between the two ground pivots |
| L2 Crank (A→B) | 182 mm | Backrest support arm |
| L3 Coupler (B→C) | 450 mm | Seat connecting link |
| L4 Rocker (C→D) | 205 mm | Footrest output link |

---

# Part 2 – CAD Modeling in Fusion 360

## 🖥️ Why Fusion 360?

I chose **Fusion 360** for this project instead of my usual SolidWorks. The deciding factor was its **parametric workflow combined with the Arrange feature**.

Here's why that matters for CNC work specifically:

- All key dimensions (material thickness, link lengths, slot widths) are defined as parameters in one place
- Changing a parameter automatically propagates through every sketch and feature in the model
- The **Arrange** feature lets me lay out all parts flat on a virtual sheet, directly reflecting any design changes
- That arranged layout can be exported directly as a **DXF** — ready for VCarve or Inkscape
- No more: change design → export → open in nesting software → re-nest → re-export → repeat forever

This made the iteration loop dramatically faster, especially when I was tweaking the linkage geometry.

![Fusion 360](../../../images/week-7/fusion-arranged.jpg)

---

## 📐 Building the Model

I started by building sketches using the link lengths from the simulator, then modeled the full chair structure around the four-bar linkage geometry.

**Components in the design:**

| Component | Description |
| --- | --- |
| Seat platform | Main sitting surface |
| Backrest | Reclines via the four-bar linkage |
| Footrest | Extends when reclining |
| Side frame (×2) | Main structural panels with pivot holes |
| Cross braces | Lateral stiffeners connecting the two side frames |
| Linkage arms | The actual four-bar links (cut from plywood) |

The complete model took almost a full day to build — getting all the pivot positions to line up correctly and ensuring the linkage moved through its full range without any part-to-part interference took a lot of back-and-forth.

![Fusion 360 full assembly — the complete recliner model in 3D](../../../images/week-7/fusion-full-assembly.jpg)

<video width="100%" controls>
  <source src="../../../images/week-7/fusion-design.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

## 🔩 Press-Fit Joinery Details

Throughout the design, I incorporated the press-fit tolerances we measured during the group assignment. The joinery uses:

- **Press-fit slot connections** for the main structural frame joints
- **Dogbone fillets** at all interior corners of slots and pockets — essential for CNC work because the router leaves a circular radius at every corner, and without dogbones the mating piece won't seat fully

### 🦴 Using the Nifty Dogbone Add-in

Rather than manually sketching dogbone fillets at every interior corner (which would have taken forever with this many slots), I used the **Nifty Dogbone** add-in for Fusion 360. This automatically generates dogbone fillets for all selected edges in one click.

**Step-by-step process:**

1. **Install the add-in** — Go to Fusion 360 → Utilities → Add-Ins → Scripts and Add-Ins. Search for "Dogbone" in the Fusion App Store. Or go directly to https://apps.autodesk.com/FUSION/en/Detail/Index?id=3534533763590670806&appLang=en&os=Win64 
and download and install it

2. **Open Add-Ins Manager** — Press `Shift + S` or go to Utilities → Add-Ins → Scripts and Add-Ins


3. **Enable Nifty Dogbone** — Find "Nifty Dogbone" and enable it. 

![Nifty Dogbone add-in enabled in Fusion 360](../../../images/week-7/nifty-enabled.jpg)

4. **Open Nifty** — With the add-in enabled, you can open it from solid -> modifty -> Nifty Dogbone

![Nifty Dogbone dialog open](../../../images/week-7/nifty-dialogue-open.jpg)

5. **Select the component** — In the dialog, select the component containing slots that need dogbones. The add-in will automatically find all interior corners on that component.

6. **Set the tool diameter** — Enter the diameter of your CNC end mill (this determines the radius of the dogbone fillet). I used the same 6mm end mill diameter we were cutting with on the ShopBot.

7. **Click OK** — The add-in automatically finds all interior corners on the selected faces and adds dogbone fillets to each one

![Nifty Dogbone parameters and settings](../../../images/week-7/nifty-parameters.jpg)

This saved me easily 2+ hours of tedious manual filleting — the chair design had dozens of interior corners across all the slots and joints.

---

## 📦 Arranging Parts and Exporting DXF

Once the design was finalized, I used Fusion's **Arrange** feature to lay all parts flat on a virtual 8ft × 4ft sheet — mimicking the actual plywood dimensions.

Then I exported the arranged layout as a **DXF file**, which I could open directly in VCarve Pro for CAM setup.

![Fusion 360 Arrange feature with all parts laid flat](../../../images/week-7/fusion-arranged.jpg)

---

# Part 3 – Cardboard Prototype

Before committing to milling full plywood, I scaled the design down and cut a cardboard prototype to verify that the mechanism actually worked.

**Scaling down the design:**

Since I had already arranged the files and exported the DXF for the full-scale plywood version, I used a simpler approach — I opened the DXF in **Inkscape** and used the **Object → Transform → Scale** functionality.

To calculate the correct scale ratio, I needed to account for both the material thickness change and the kerf difference:
- Original: **17.5 mm plywood**
- Target: **3 mm cardboard** with **0.33 mm kerf**

Using the ratio calculation, I scaled the entire design proportionally to fit the cardboard dimensions while maintaining all the joint tolerances. This was much faster than going back to Fusion and re-exporting.

![Using Inkscape's Transform → Scale to resize the DXF](../../../images/week-7/inkscape-transform.jpg)

**Assembly:**

I assembled the cardboard prototype using aluminum shielded wire as pivot pins — perfect for testing linkage motion at this scale.

<video width="100%" controls>
  <source src="../../../images/week-7/Cardboard-Prototype.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

**Result:** The linkage worked perfectly. The backrest reclined smoothly, the footrest extended correctly, and no parts collided throughout the full range of motion. ✅

---

# Part 4 – Ergonomic Analysis in CATIA

Before cutting full-scale plywood, I performed an ergonomic analysis of the chair to confirm it would actually be comfortable to sit in.

## 📊 RULA Analysis

I imported the chair design into **CATIA** and ran **RULA (Rapid Upper Limb Assessment)** — evaluates the posture of the upper body (neck, arms, wrists, shoulders)

This wasn't my first time running ergonomic analyses on seating designs, so I was familiar with the process. The analysis was run for both the upright seated position and the reclined position.

![CATIA RULA analysis — upright seated position showing the posture score](../../../images/week-7/rula.jpg)

**Results:**

| Analysis | Position | Score |
| --- | --- | --- |
| RULA | Upright | 2 |


The results confirmed the chair provides a comfortable posture in both positions. Any minor issues flagged by RULA in the upright position were acceptable given that the primary use case is the reclined position.

---

# Part 5 – CNC Machining on the ShopBot

## 🗂️ VCarve Pro CAM Setup

With the design confirmed and the ergonomics validated, it was time to set up the actual CNC toolpaths in VCarve Pro.

**Cutting parameters used:**

| Parameter | Value |
| --- | --- |
| End mill diameter | 6 mm |
| Pass depth | 4.5 mm |
| Feed rate | 1200.2 mm/min |
| Plunge rate | 1200 mm/min |
| Spindle speed | 1200 RPM |
| Tab width | 5 mm |
| Tab height | 3 mm |


### Machine Setup Workflow

Before running any job, we went through the standard ShopBot setup procedure:

1. **Set X and Y limits** — establishing the machine's coordinate reference point on the bed
2. **Secure the workpiece** — the blank plywood sheet is screwed down to the bed to prevent any movement during machining
3. **Set X, Y, Z offsets relative to the workpiece** — zeroing out the tool position relative to the top surface of the material

---

### Toolpath Generation in VCarve Pro

For generating toolpaths, we used **VCarve Pro** — the standard CAM software that ships with the ShopBot system. Here's the complete workflow I followed to prepare my design for machining.

---

#### Step 1: Create a New Project

Open VCarve Pro and select **Create New File** to start a new project.

![VCarve Pro — Creating a new file](../../../images/week-7/vcarve-1.jpg)

---

#### Step 2: Set Material Dimensions

Configure the job setup by entering the material dimensions and thickness. For my project, I set the sheet size to match the 8ft × 4ft plywood sheet with a thickness of 17.5 mm.

![VCarve Pro — Setting material dimensions and thickness](../../../images/week-7/vcarve-3.jpg)

---

#### Step 3: Import the Vector File

Import the DXF file exported from Fusion 360. Go to **File → Import → Import Vectors** and select your DXF file.

![VCarve Pro — Importing vectors (part 1)](../../../images/week-7/vcarve-4.jpg)
![VCarve Pro — Importing vectors (part 2)](../../../images/week-7/vcarve-5.jpg)
![VCarve Pro — Vectors imported successfully](../../../images/week-7/vcarve-6.jpg)

---

#### Step 4: Position the Design

Move and align the imported vectors to fit properly on the workpiece canvas. Use the **Move** and **Align** tools to position all parts within the material boundaries.

![VCarve Pro — Positioning vectors on the canvas](../../../images/week-7/vcarve-7.jpg)

Click **Apply and Close** to confirm the positioning.

![VCarve Pro — Apply and close the positioning dialog](../../../images/week-7/vcarve-9.jpg)

---

#### Step 5: Create Screw Hole Markers

Before cutting any parts, we need to secure the workpiece to the spoil board. Create circles at strategic locations (corners and center areas away from parts) to mark where screws will be drilled.

![VCarve Pro — Creating circles for screw hole positions](../../../images/week-7/vcarve-10.jpg)
![VCarve Pro — Selecting Drilling Toolpath from the menu](../../../images/week-7/vcarve-11.jpg)
![VCarve Pro — Selecting the drill bit](../../../images/week-7/vcarve-12.jpg)

---

#### Step 6: Set Up the Drilling Toolpath

Navigate to the **Toolpath** menu and select **Drilling Toolpath**. This will create the toolpath for drilling the screw holes.

![VCarve Pro — Configuring drilling parameters (part 1)](../../../images/week-7/vcarve-13.jpg)

Select the appropriate drill bit from the tool library and configure the drilling parameters:

![VCarve Pro — Drilling toolpath complete](../../../images/week-7/vcarve-15.jpg)

![VCarve Pro — Selecting vectors for inside cuts](../../../images/week-7/vcarve-16.jpg)
![VCarve Pro — Profile toolpath settings for inside cuts](../../../images/week-7/vcarve-17.jpg)
![VCarve Pro — Configuring the end mill parameters](../../../images/week-7/vcarve-19.jpg)

---

#### Step 7: Create Inside and Outside Profile Toolpaths

Select all vectors representing internal cuts (slots, holes, and interior pockets). Apply the **Profile Toolpath** with the **Inside/Left** cutting direction. This ensures the tool cuts on the inside of closed shapes followed by the **Outside/Right** cutting direction for the outer contours as a second profile toolpath.

![VCarve Pro — Setting pass depth and feed rates](../../../images/week-7/vcarve-20.jpg)
![VCarve Pro — Adding tabs to hold parts in place](../../../images/week-7/vcarve-21.jpg)
![VCarve Pro — Tab configuration settings](../../../images/week-7/vcarve-22.jpg)
![VCarve Pro — Inside profile toolpath preview](../../../images/week-7/vcarve-23.jpg)
![VCarve Pro — Outside profile toolpath configuration](../../../images/week-7/vcarve-25.jpg)
![VCarve Pro — Final toolpath overview](../../../images/week-7/vcarve-26.jpg)

---

#### Toolpath Types Summary

| Toolpath Type | Purpose |
| --- | --- |
| **Drilling** | Creates screw holes to secure the workpiece |
| **Profile (Inside)** | Cuts internal slots, holes, and interior shapes |
| **Profile (Outside)** | Cuts the outer contour of parts to release them |
| **Pocket** | Clears material from enclosed areas |

---

#### Recommended Cutting Order

The sequence of operations matters for successful CNC machining:

1. **Drilling first** — Secure the workpiece with screws before any cutting begins
2. **Pockets second** — Clear any recessed areas while the material is still fully supported
3. **Inside profiles third** — Cut all internal features (slots, holes)
4. **Outside profiles last** — Final cuts to release parts, with tabs keeping everything in place until the job completes

<video width="100%" controls>
  <source src="../../../images/week-7/simulating-toolpath.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

Adding the z-offset
<div style="text-align: center;">
  <video width="100%" controls>
    <source src="../../../images/week-7/group-2.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>
---

## 🔧 Running the Job

With the ShopBot set up and the workpiece secured, I sent the toolpath file and ran the job.

![ShopBot setup](../../../images/week-7/shopbot-2.jpg)
![ShopBot workpiece secured](../../../images/week-7/shopbot-3.jpg)
![ShopBot ready to cut](../../../images/week-7/shopbot-4.jpg)

<video width="100%" controls>
  <source src="../../../images/week-7/Drilling.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

<video width="100%" controls>
  <source src="../../../images/week-7/Cnc-Routing.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

# Part 6 – Post-Processing

## ✂️ Tab Removal

After the CNC job finished, the first step was removing the parts from the sheet by cutting through the tabs.

![Parts after CNC cutting](../../../images/week-7/shopbot-5.jpg)
![Removing tabs](../../../images/week-7/shopbot-6.jpg)
![Parts removed from sheet](../../../images/week-7/shopbot-7.jpg)
![All parts laid out](../../../images/week-7/shopbot-8.jpg)

---

## 🪵 Sanding

Once all the parts were freed, I sanded all surfaces to smooth out any machining marks and rough edges. I worked through grits progressively — starting coarser to remove tool marks, finishing finer for a smooth surface.

<video width="100%" controls>
  <source src="../../../images/week-7/filing.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

## 🔵 Edge Filleting with a Wood Router

To improve both the aesthetics and user comfort of the chair (you don't want sharp plywood edges digging into your legs), I used a **wood router fitted with a fillet / roundover bit** to round off all the exposed edges.

This step made a huge visible difference — the chair went from looking like a raw CNC project to looking like something deliberately designed.

<video width="100%" controls>
  <source src="../../../images/week-7/sanding.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

# Part 7 – Assembly

With all parts post-processed, it was time to put it all together.

The press-fit joints assembled without any glue — the tolerances from the group assignment test gauge meant everything locked together firmly with hand pressure.

The pivot joints for the four-bar linkage were assembled using bolts and locking nuts, allowing the linkage to rotate freely while staying tight enough not to wobble.

<video width="100%" controls>
  <source src="../../../images/week-7/final-assembly.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

# Hero Shots

<div style="display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; margin-bottom: 15px;">
  <img src="../../../images/week-7/hero-2.jpg" alt="Hero shot 2" style="width: 100%; border-radius: 8px;">
  <img src="../../../images/week-7/hero-3.jpg" alt="Hero shot 3" style="width: 100%; border-radius: 8px;">
  <img src="../../../images/week-7/hero-4.jpg" alt="Hero shot 4" style="width: 100%; border-radius: 8px;">
</div>

<div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; max-width: 66%; margin: 0 auto 15px auto;">
  <img src="../../../images/week-7/hero-6.jpg" alt="Hero shot 6" style="width: 100%; border-radius: 8px;">
  <img src="../../../images/week-7/hero-8.jpg" alt="Hero shot 8" style="width: 100%; border-radius: 8px;">
</div>

<div style="text-align: center;">
  <video width="60%" controls>
    <source src="../../../images/week-7/hero.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

<div style="text-align: center;">
  <video width="100%" controls>
    <source src="../../../images/week-7/hero-sitting-1.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

---

## Helpful Websites

- ShopBot Documentation — https://www.shopbottools.com/support/
- VCarve Pro by Vectric — https://www.vectric.com/products/vcarve-pro
- Fusion 360 Arrange Feature — https://help.autodesk.com/view/fusion360/ENU/
- Chair 4-Bar Linkage Calculator (my simulator) — [../chair-4-bar-linkage-calculator/](../chair-4-bar-linkage-calculator/)
- RULA Ergonomic Assessment — https://ergo.human.cornell.edu/ahRULA.html
- REBA Ergonomic Assessment — https://ergo.human.cornell.edu/ahREBA.html

---

## Reflection

This was probably the most satisfying week so far. Every previous week built up skills that I ended up using here — the parametric design thinking from Week 2, the press-fit knowledge from Week 3, the ergonomics background from before Fab Academy. It all came together in one object I can actually sit in.

The four-bar linkage was the part I was most nervous about — it's one thing to see it work on paper or in a simulator, and a completely different thing to cut it out of plywood and have it actually move. When the cardboard prototype worked first try, I was honestly surprised. When the full-scale chair reclined smoothly on the first assembly attempt, that was a great feeling.

The parametric Fusion 360 workflow genuinely saved me hours — every time I tweaked the linkage dimensions the DXF update was automatic. That's the kind of thing that sounds boring until you've done it the painful manual way a few times.

Next up: Electronics Production week. Time to actually mill the PCB I designed in Week 6 😎

---
<div style="text-align: center; margin: 40px 0; padding: 30px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); border-radius: 12px; box-shadow: 0 8px 20px rgba(0,0,0,0.15);">
  <a href="/files/week-7.rar" target="_blank" style="display: inline-block; padding: 14px 32px; background-color: white; color: #667eea; font-weight: bold; font-size: 16px; text-decoration: none; border-radius: 8px; transition: all 0.3s ease; box-shadow: 0 4px 12px rgba(0,0,0,0.15);" onmouseover="this.style.transform='translateY(-2px)'; this.style.boxShadow='0 6px 16px rgba(0,0,0,0.25);'" onmouseout="this.style.transform='translateY(0)'; this.style.boxShadow='0 4px 12px rgba(0,0,0,0.15);'">
    ⬇️ Download All Files from Week 7
  </a>
</div>
