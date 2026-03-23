+++
title = "Week 03 - Computer Controlled Cutting"
weight = 103
bookCollapseSection = true
+++
# Week 03 – Computer Controlled Cutting

So its my **third week of Fab Academy**, and yeah its special because its **week 3** 😄  
also im lowkey a fan of multiples of 3 so lets go with that.

Week 3 focused on **computer-controlled cutting**, specifically using the **laser cutter** and **vinyl cutter**.  
The aim was to understand how digital designs translate into precise physical parts, and how machine parameters like **kerf, speed, and power** directly affect accuracy and fit.

This week built naturally on **Week 1 (principles, tools, documentation)** and **Week 2 (CAD and parametric design)**, where design intent and parametric thinking were already established. Here, those designs were finally tested against real machines and materials.

---

<div style="display: flex; gap: 20px; justify-content: center; margin: 30px 0; overflow: hidden;">
  <img src="/images/week-3/hero-cyberpunk-1.jpg" alt="Computer Controlled Cutting Setup 1" style="flex: 1; max-width: 400px; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); display: block;">
  <img src="/images/week-3/hero-cyberpunk-2.jpg" alt="Computer Controlled Cutting Setup 2" style="flex: 1; max-width: 400px; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); display: block;">
</div>

---

## Group Assignment
- Completed **lab safety training**
- Characterized the **laser cutter** by testing:
  - Focus  
  - Power  
  - Speed  
  - Rate  
  - Kerf  
  - Joint clearance  
  - Different joint types  

---

## Individual Assignment
- Cut a design using the **vinyl cutter**
- Designed and laser-cut a **parametric construction kit**
- Accounted for **laser kerf** in the design
- Documented the design, cutting process, and assembly

### Extra Credit Goals
- Designed parts that can be **assembled in multiple ways**
- Included **non-flat / interlocking elements**
- Used **engraving along with cutting**

---

## What I Learned
- Laser cutting accuracy depends heavily on **machine calibration and material testing**
- Kerf varies with **material, power, speed, and focus**
- Parametric design makes it easier to adapt designs after kerf testing
- Press-fit joints require balancing **tight fit and material safety**
- Vinyl cutting requires a different mindset compared to laser cutting
- Proper documentation helps reproduce results and avoid repeated mistakes

---

## Software Used
- **Laser Cutter Control Software - Trotec Job Control** for sending jobs to the laser cutter
- **Browser + Git** for documentation (same workflow as Week 1 & 2)
- **Mods Project** for sending vinyl cutting jobs
- **Inkscape** for preparing cutting files
- **Fusion 360** for parametric modeling
- **Deepnest** for nesting the construction kit parts https://deepnest.io/
- **Bambu Studio** for creating the 3d model of a human from image https://www.bambulab.com/bambu-studio
- **kiri:moto** for slcing 3d model into the svg files for laser cutting https://grid.space/kiri/


<a href="laser-gauge-tool/" style="display: inline-flex; align-items: center; gap: 8px; margin-top: 16px; padding: 12px 20px; background: linear-gradient(135deg, #7c3aed 0%, #a855f7 100%); color: white; text-decoration: none; border-radius: 8px; font-weight: 500; transition: all 0.2s; box-shadow: 0 4px 12px rgba(124, 58, 237, 0.3);">
  🛠️ Open Laser Gauge Tool
</a>

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | and introduction to computer-controlled cutting |
| THU | Lab safety training |
| FRI | Laser cutter characterization and kerf testing Joint clearance testing and press-fit experiments |
| SAT | Parametric construction kit design |
| SUN | Parametric construction kit design (Continued)|
| MON | Vinyl cutting , Laser cutting and engraving , assembly testing |
| TUE | Documentation and regional review |

---

## Lab Safety Training

I’m adding the group assignment page here for reference:

🔗 https://fabacademy.org/2026/labs/kochi/group_assignmetns/week03/

---

## My Reflection on Lab Safety

One thing that really hit me this week is that the machines in the lab are **not kids toys**.  
They are powerful tools that can hurt you in very serious ways if you’re careless.  
So you need to treat the machines with **mutual respect** and be extremely alert while working with them.

---

## Lab Safety Training (Individual Understanding)

### General Lab Safety

Safety is the top priority in the lab. Before operating any machine or handling materials, it is important to understand the risks involved. The lab contains high-powered machines, sharp tools, chemicals, and pressurized systems.

From the training, these were the main safety practices I learned and followed:

- Always wear proper PPE such as safety glasses, gloves, and closed-toe shoes  
- Avoid loose clothing, jewelry, and keep long hair tied back  
- Maintain a clean and organized workspace to avoid accidents  
- Check machines before use and report any issues immediately  
- Be aware of emergency stops, fire extinguishers, first-aid kits, and eyewash stations  

The locations of the fire extinguisher, emergency exits, and the lab floor plan were also clearly explained.

![extinguisher](/images/week-3/safety-1.jpg)

---

### CO₂ Laser Cutter Safety

The CO₂ laser cutter is a powerful machine used for cutting and engraving. Because of the high-intensity laser beam, it poses risks such as fire hazards, eye injury, and exposure to toxic fumes.

Certain materials like **PVC and ABS should never be laser cut**, as they release hazardous gases.

---

### Exhaust System

The laser cutter is equipped with an exhaust filtration system that removes smoke and fumes generated during cutting. The system uses filters and activated charcoal to absorb harmful gases and VOCs released from materials like wood and acrylic.

Before cutting:
- The exhaust system must be ON  
- The laser must be properly focused  
- The material should be secured on the bed  
- Room temperature should be maintained for safe operation  

![exhaust system](/images/week-3/trotec-2.jpg)   
![temperature monitor](/images/week-3/trotec-3.jpg)

During cutting, the machine must be continuously monitored to prevent fires. If a fire occurs, the machine should be paused immediately while keeping the lid closed. A CO₂ fire extinguisher should be used if required.

---

### What to Do If a Fire Starts in the Laser Cutter

1. Do not open the lid immediately  
2. Pause the laser cutter if it is safe to do so  
3. Cover small flames with a larger non-flammable material  
4. Monitor the situation  
5. Use a CO₂ fire extinguisher if needed  
6. Call for help and evacuate if the fire cannot be controlled  

---

### Vinyl Cutter Safety

The vinyl cutter also requires careful handling:

- Blade must be installed correctly and adjusted to proper depth  
- Vinyl sheet must be aligned properly  
- Hands should be kept away from moving parts  
- Machine should be paused before clearing jams  
- Excess vinyl should be removed carefully using a weeding tool  

---

## Vinyl Cutting

### Machine Used
**Roland CAMM-1 Servo – Vinyl Cutter**

A vinyl cutter is a computer-controlled machine that uses a blade to make precise cuts on vinyl sheets. It is mainly used for stickers, decals, and signage.
![Vinyl Cutter](/images/week-3/vinyl-cutter.jpg)
https://www.rolanddga.com/support/products/cutting/camm-1-gx-24-24-vinyl-cutter

### Machine Controls
- Roll or sheet selection  
- Maximum cutting force  
- Cutting tool and blade depth  
![Vinyl controls](/images/week-3/roland-1.jpg)

### Setup Process
- Load vinyl by releasing the loading lever  
- Align vinyl with pinch rollers  
- Lock the lever  
- Inspect and adjust blade depth  
- Set origin and perform a test cut  

---

## Vinyl Project – Tarusa Motorsports Sticker

This week I designed and cut a sticker for **Tarusa Motorsports**, the off-road buggy building team I am part of.
https://www.instagram.com/tarusamotorsport/

Workflow:
- Opened Inkscape  
  ![Import Logo](/images/week-3/vinyl-2.jpg)
- Imported the team logo  
  ![Inkscape Start](/images/week-3/vinyl-1.jpg)
  ![Trace Bitmap](/images/week-3/vinyl-3.jpg)
- Used **Trace Bitmap** to convert it into a vector  
  ![Clean Vector](/images/week-3/vinyl-4.jpg)
  ![Vector Adjustment](/images/week-3/vinyl-5.jpg)
  ![Final Paths](/images/week-3/vinyl-6.jpg)
- Cleaned the vector and adjusted paths  
- Arranged multiple sizes on the canvas  
  ![Multiple Sizes](/images/week-3/vinyl-7.jpg)
- Sent the file for cutting using the Mods Project workflow  

## Vinyl Cutting Using Mods Project

For sending the vinyl cutting job to the machine, I used the **Mods Project** web application.

I first opened the Mods Project website:

https://modsproject.org/

![Mods Project Website](/images/week-3/vinyl-mods-1.jpg)

---

### Selecting the Program

After opening the site, I right-clicked on the page and selected:

**Program**

![Program Menu](/images/week-3/vinyl-mods-2.jpg)

Then I clicked on **Open Program**.

![Program Interface](/images/week-3/vinyl-mods-3.jpg)

---

### Machine and Process Selection

From the available options, I selected:
- **Roland** as the machine
- Chose the appropriate **machine model**
- Selected **Cut** as the process

![Machine Selection](/images/week-3/vinyl-mods-4.jpg)

---

### Loading File and Cutting

Next steps:
- Loaded the **SVG file**
- Clicked **Calculate** to generate toolpaths
- Performed a **test cut** to verify blade depth and force
- Sent the file to the vinyl cutter for final cutting

![File Loading and Calculation](/images/week-3/vinyl-mods-5.jpg)

---

The cutting process completed successfully after verifying the test cut, and the final vinyl output was obtained.

**Vinyl Cutting Process:**

<video autoplay loop width="100%" height="auto" controls style="display: block;">
  <source src="/images/week-3/vinyl.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

Final output after cutting:  
![Vinyl Cutting Result](/images/week-3/vinyl-8.jpg)

Transfer paper was applied so the stickers could be mounted easily:  
![Transfer Paper](/images/week-3/vinyl-9.jpg)

Final hero shots:  
![Final Sticker 1](/images/week-3/vinyl-10.jpg)
![Final Sticker 2](/images/week-3/vinyl-11.jpg)

---

## Laser Cutting  

### Machine Used  
**Trotec Speedy 100 – Laser Cutter & Engraver**  
![Trotec Speedy 100](/images/week-3/trotec-1.jpg)

A laser cutter is a computer-controlled machine that uses a focused laser beam to cut, engrave, or mark materials such as wood, acrylic, paper, leather, and certain plastics with high precision.  

Buy / Product link:  
https://www.troteclaser.com/en/laser-machines/laser-engravers-speedy-series  

---

### Machine Controls  
- Laser power (%)  
- Cutting speed (mm/s)  
- Frequency / PPI  
- Focus height  
- Air assist and exhaust control  
- Job origin and alignment  
![Machine Controls 1](/images/week-3/trotec-5.jpg)
![Machine Controls 2](/images/week-3/trotec-4.jpg)
---

### Setup Process  
1. Place material on the cutting bed (honeycomb or flat bed).  
2. Adjust focus using the focus tool or autofocus.  
3. Set origin (usually top-left or center).  
4. Select material preset or manually set power & speed.  
5. Run a small test cut.  
6. Start full job and monitor cutting.  
7. Turn on exhaust and air assist during operation.  

---

### Materials Commonly Used  
- Plywood / MDF  
- Acrylic (PMMA)  
- Cardboard  
- Leather  
- Paper  
- Fabric  

> ⚠️ Do NOT cut PVC or vinyl — toxic chlorine gas is released.  

## Parametric Designing
This week’s individual assignment was to design a **parametric construction kit** that could be laser cut and assembled.  
The design had to account for **laser kerf** to ensure proper fit and function.

**Things to consider from group assignment:**
- Kerf - 0.3mm 
- Material thickness - 3mm cardboard
- Press fit joints - 0.2mm clearance

### Parametric Construction Kit

For the construction kit, I followed the same parametric workflow as the kerf comb.

The idea was to design **10 different parts** that together form a universal construction kit.  
The design was fully parametric so it could adapt to:
- Different material thicknesses  
- Different materials  
- Different laser kerf values  

### Parametric Construction Kit – Detailed Workflow

**Steps followed:**

- Opened **Fusion 360** and set up all required parameters for the construction kit  
  ![Construction Kit Setup](/images/week-3/construction-kit-1.jpg)

- Modeled all **10 individual components** using parametric sketches  
  ![Construction Kit Components](/images/week-3/construction-kit-2.jpg)

- Extruded the components and added chamfers to the press-fit edges to improve fit  
  ![Construction Kit Extrude](/images/week-3/construction-kit-3.jpg)

- Projected the geometry onto a new sketch and prepared it for export  
  ![Construction Kit Projection](/images/week-3/construction-kit-4.jpg)

- Exported the sketches as **DXF** files  
  ![Construction Kit exporting 1](/images/week-3/construction-kit-5.jpg)  
  ![Construction Kit exporting 2](/images/week-3/construction-kit-6.jpg)  
  ![Construction Kit exporting 3](/images/week-3/construction-kit-7.jpg)

---

### Preparing the DXF in Inkscape

- Imported the exported DXF into **Inkscape**  
  ![Construction Kit Inkscape Import](/images/week-3/construction-kit-8.jpg)

- Ungrouped all parts using **Ctrl + Shift + G**, rearranged them, and grouped them back using **Ctrl + G**  
  ![Construction Kit Ungroup and Arrange](/images/week-3/construction-kit-9.jpg)

- Selected all objects (**Ctrl + A**) and set:
  - Fill: **No fill**
  - Stroke color: **Red**  
  ![Construction Kit Stroke Color](/images/week-3/construction-kit-10.jpg)

- Resized the canvas to fit the objects using **Ctrl + Shift + R**  
  ![Construction Kit Resize Canvas](/images/week-3/construction-kit-11.jpg)

- Selected all objects again and set the **stroke width to 0.1 mm** in Stroke Style  
  ![Construction Kit Stroke Width](/images/week-3/construction-kit-12.jpg)

---

### Nesting Using Deepnest

- Exported the file and opened it in **Deepnest** for nesting  
  ![Deepnest UI](/images/week-3/construction-kit-13.jpg)
  ![Deepnest Svg Imported](/images/week-3/construction-kit-14.jpg)

- Added the sheet size corresponding to the cardboard used  
  ![Deepnest Sheet Size](/images/week-3/construction-kit-15.jpg)

- Set the required quantity for the construction kit parts  
  ![Deepnest Quantity](/images/week-3/construction-kit-16.jpg)

- Started the nesting process to optimize material usage  
  ![Deepnest Nesting Process](/images/week-3/construction-kit-17.jpg)

- After nesting was completed, exported the file as an **SVG**  
  ![Deepnest Export](/images/week-3/construction-kit-18.jpg)

---

### Laser Cutting

- Imported the nested SVG into **Trotec Job Control** and set the required power and speed values  
  

- Started the laser cutting process  

**Laser Cutting Process:**

<video autoplay loop width="50%" height="auto" controls style="display: block;">
  <source src="/images/week-3/laser.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

### Final Output

**Hero shot of the completed construction kit:**  
![Construction Kit Final](/images/week-3/construction-kit-19.jpg)

**Hero shots of the assembled construction kit:**  
Take a look at what i had build

![Construction Kit artillery gun](/images/week-3/construction-kit-191.jpg)
![Construction Kit Assembled 1](/images/week-3/construction-kit-20.jpg)
![Construction Kit Assembled 2](/images/week-3/construction-kit-21.jpg)
![Construction Kit Assembled 3](/images/week-3/construction-kit-22.jpg)
![Construction Kit Assembled 2](/images/week-3/construction-kit-23.jpg)
![Construction Kit Assembled 3](/images/week-3/construction-kit-24.jpg)

## Compression Testing Comb (Fusion 360)

My first design task this week was creating a **compression testing comb** as part of the group-related work.  
I flipped a coin between SolidWorks and Fusion 360, and **Fusion 360** won.

Workflow:
- Opened Fusion 360 and opened the parameters tab  
  ![Parametric Setup](/images/week-3/parametric-1.jpg)
- Defined all required parameters for the kerf gauge  
  ![Parametric Parameters](/images/week-3/parametric-2.jpg)
- Modeled the entire sketch  
  ![Parametric Sketch](/images/week-3/parametric-3.jpg)
- Extruded the sketch  
  ![Parametric Extrude](/images/week-3/parametric-4.jpg)
- Applied fillets where needed  
  ![Parametric New Sketch](/images/week-3/parametric-5.jpg)
- Created a new sketch  
- Projected the extruded shape onto the sketch  
  ![Parametric New Sketch](/images/week-3/parametric-projection.jpg)
- Exported the sketch as DXF  
- Opened the DXF in Inkscape  
  ![Parametric Inkscape](/images/week-3/parametric-6.jpg)

In Inkscape, I ensured:
- All cut paths were strokes  
- Engraving areas were fills  

I then sent the file to the **Trotec laser cutter**, adjusted power and speed values in the Job Control software, and completed the cut and engraving.

![Parametric Inkscape](/images/week-3/kerf-test.jpg)

---
## Making a Laser Cut Layered Statue

After completing the assignments for the week, I planned to make something additional — a **laser-cut layered statue**.  

The idea was to create a 3D model composed of multiple 2D laser-cut layers stacked together, similar in concept to how a 3D printer builds objects layer by layer.

---

### Step 1 – Generating the 3D Model

First, I needed a 3D model. I thought it would be interesting to make a statue of **Neil**.

I searched online and found a suitable image of him.

Then I opened **Bambu Studio**, navigated to the **Maker Lab** section, and selected the **“Make My Statue”** option. I uploaded the image of Neil into the tool.

![Neil Upload](/images/week-3/neil-1.jpg)

The software then began processing the image into a 3D model.

![Neil Processing 1](/images/week-3/neil-2.jpg)  
![Neil Processing 2](/images/week-3/neil-3.jpg)

After processing, it generated a rendered 3D output, which I exported as an **STL file**.

![Neil Rendered STL](/images/week-3/neil-4.jpg)

---

### Step 2 – Modifying the Model in 3D Builder

Next, I imported the STL file into **3D Builder** (which I had previously used in Week 2).

To allow structural support during assembly, I created:

- Two cylinders  
- 200 mm height  
- 8 mm diameter  

These were positioned inside the model.

Then I performed a **Boolean subtraction** to remove the volume of the cylinders from the statue. This created two internal holes that would later allow threaded rods to pass through and hold the stacked layers together.

![Cylinder Boolean 1](/images/week-3/neil-5.jpg)  
![Cylinder Boolean 2](/images/week-3/neil-6.jpg)

After completing this modification, I saved the updated STL file.

---

### Step 3 – Slicing for Laser Cutting (Kiri:Moto)

I then imported the modified STL into **Kiri:Moto** and switched to **Laser Mode**.

Material used:
- 2 mm thick cardboard  
- Kerf value set to 0.3 mm  

After entering the material thickness and kerf values, I sliced the model into layers.

![Kiri Moto Setup](/images/week-3/neil-7.jpg)  
![Kiri Moto Slicing](/images/week-3/neil-8.jpg)

The slices were exported as **SVG files**.

---

### Step 4 – Organizing Layers in Inkscape

The exported SVG files were opened in **Inkscape**.

To make assembly easier, I labeled the individual layers numerically (1, 2, 3… up to 78).

This numbering system helped during stacking and alignment.

![Layer Numbering](/images/week-3/neil-9.jpg)

---

### Step 5 – Nesting in Deepnest

The labeled SVG files were then imported into **Deepnest** for nesting.

![Deepnest Import](/images/week-3/neil-10.jpg)

After nesting was completed, the optimized layout files were exported.

---

### Step 6 – Laser Cutting

The nested SVG file was opened in **Trotec Job Control**.

The 2 mm cardboard sheet was placed on the laser bed, and appropriate power and speed values were set.

The cutting process was then started.

![Laser Cutting 1](/images/week-3/neil-11.jpg)  
![Laser Cutting 2](/images/week-3/neil-12.jpg)

---

### Final Assembly – Hero Shots

After cutting all the layers, the pieces were stacked in order and aligned using the threaded rods inserted through the internal holes.

Final assembled layered statue:

![Final Statue 1](/images/week-3/neil-13.jpg)  
![Final Statue 2](/images/week-3/neil-14.jpg)  
![Final Statue 3](/images/week-3/neil-15.jpg)

---

---

## Creating the Base for the Statue

The next step was designing and fabricating the **base** for the layered statue.

First, I measured the required dimensions for the box that would hold and support the statue. Based on those dimensions, I used the following parametric box generator:

🔗 https://cuttle.xyz/@cuttle/Open-Box-with-Finger-Joints-D2ugGEvYUNfd

Using this tool, I entered:
- Required length
- Width
- Height
- Material thickness

The tool automatically generated an **open box with finger joints**, which was suitable for laser cutting.

After generating the box layout, I exported the design as an **SVG file**.

---

### Editing in Inkscape

The exported SVG was opened in **Inkscape**, where:

- I added the required text on the base
- Ensured all cut paths were strokes
- Verified stroke width was suitable for laser cutting

Once the design was finalized, the file was sent to the **Trotec laser cutter**.

---

### Laser Cutting and Assembly

The box parts were laser cut from cardboard using the appropriate power and speed settings.

After cutting:
- The finger joints were aligned
- The box was assembled manually
- The statue was mounted onto the base

---

### Final Base + Statue – Hero Shots

![Statue Base 1](/images/week-3/neil-hero-1.jpg)  
![Statue Base 2](/images/week-3/neil-hero-2.jpg)  
![Statue Base 3](/images/week-3/neil-hero-3.jpg)

---

## Wait a second… something was missing — THE GLASSES 😤👓 {#glasses}  

So instead of redesigning anything fancy, I just bent some solder wire and made the glasses manually and attached them to the statue 😌🔥  

![Neil Glasses 1](/images/week-3/neil-glasses-1.jpg)  
![Neil Glasses 2](/images/week-3/neil-glasses-2.jpg)


## Final Reflection

This week made it very clear that **designing is only half the job**.  
Understanding machine behavior, safety, kerf, and material limitations is just as important.  
Week 3 successfully bridged the gap between digital design and physical fabrication.

---

<div style="text-align: center; margin: 40px 0; padding: 30px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); border-radius: 12px; box-shadow: 0 8px 20px rgba(0,0,0,0.15);">
  <a href="/files/week-3.rar" target="_blank" style="display: inline-block; padding: 14px 32px; background-color: white; color: #667eea; font-weight: bold; font-size: 16px; text-decoration: none; border-radius: 8px; transition: all 0.3s ease; box-shadow: 0 4px 12px rgba(0,0,0,0.15);" onmouseover="this.style.transform='translateY(-2px)'; this.style.boxShadow='0 6px 16px rgba(0,0,0,0.25);'" onmouseout="this.style.transform='translateY(0)'; this.style.boxShadow='0 4px 12px rgba(0,0,0,0.15);'">
    ⬇️ Download All Files from Week 3
  </a>
</div>

---

