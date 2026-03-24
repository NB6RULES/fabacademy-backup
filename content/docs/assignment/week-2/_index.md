+++
title = "Week 02 - Computer Aided design"
weight = 102
bookCollapseSection = true
+++

# Week 2 – Computer-Aided Design (CAD)


This week was focused on **Computer-Aided Design (CAD)**.  
The main goal was to understand how designs move from **2D to 3D**, learn the difference between **raster and vector images**, and explore different **3D modeling approaches** such as **B-Rep** and **F-Rep**.

Rather than focusing on a single software, this week emphasized understanding **design workflows**, **file types**, and **how design decisions affect fabrication**.

---

## What I Learned This Week

### 2D Design
- Difference between **raster** and **vector** images
- Raster editing tools:
  - Photopea
  - Affinity 
- Vector design tools:
  - Inkscape
  - Affinity Designer

### 3D Design
- Different types of 3D modeling:
  - Boundary Representation (B-Rep)
  - Function Representation (F-Rep)
- Introduction to parametric and non-parametric workflows
- Focused learning on:
  - Fusion 360
  - SolidWorks
  - Blender

---

## Software Used

### 2D Tools
- Affinity Designer  
- Photopea  
- Inkscape  

### 3D Tools
- Fusion 360  
- SolidWorks  
- Blender  
- 3D Builder
- OpenSCAD
- TinkerCAD
- Onshape

### Other Tools
- HandBrake (for video compression)

---

## Licensing and Software Access

Fab Academy provided access to **both Fusion 360 and SolidWorks** as part of the course.

- **Fusion 360**
  - Access was provided through **Fab Academy**
  - I already had prior experience with the software and continued using it for modeling and exploration

- **SolidWorks**
  - Access was provided through the **Fab Academy Makers / Makerspace license**
  - My existing student license was about to expire, so I opted to use the Fab Academy provided license
  - Installation was done using the **3DEXPERIENCE Launcher** and the SolidWorks installation manager

- **Onshape**
  - Access provided through **Fab Academy** (cloud-based CAD)

Since I am already familiar with **Fusion 360** and **SolidWorks**, I decided to use these tools for most of my work during Fab Academy.

---

## Weekly Assignment

### Individual Assignment
- Model (raster, vector, 2D, 3D, render, animate, simulate, etc.) a possible **final project**
- Compress images and videos
- Upload design files and explanations to the documentation page

---

## Weekly Schedule

| Day | What I Did |
|-----|----------|
| WED | Catch-up session with Neil |
| THU | Exploring Fusion 360 |
| FRI | Introduction to raster and vector tools |
| SAT | Exploring SolidWorks |
| SUN | Creating 2D and 3D models |
| MON | Continued modeling |
| TUE | Regional review |

---

## Understanding Raster vs Vector Graphics

### Vector Graphics
- Vector files use **mathematical equations** to define shapes and curves
- Each element is defined by paths and functions
- Can be scaled infinitely without losing quality
- Commonly used for:
  - Logos
  - Laser cutting
  - CNC machining
  - SVG and DXF files

### Raster Graphics
- Raster images are composed of **pixels**
- Image quality depends on resolution
- Zooming in causes pixelation
- Commonly used for:
  - Photographs
  - Textures
  - Image editing

As someone with limited prior experience in 2D design, this comparison helped me understand why **vector graphics are preferred for digital fabrication**.

![Raster vs Vector Comparison](../../../images/week-2/rastor-vs-vector.jpg)

![Raster vs Vector Example](../../../images/week-2/rastor-vs-vector1.jpg)

The explanation of raster and vector graphics was referenced from  
https://vector-conversions.com/vectorizing/raster_vs_vector.html

---
## Installing the Required Software (Windows)

### Vector Design
- **Inkscape**
  - Downloaded from the official website: https://inkscape.org/release/
  - Installed using the Windows installer
  - Used for creating and editing vector (SVG/DXF) files

![Inkscape Interface](../../../images/week-2/inkscape-interface.jpg)

### Raster Design
- **Photopea**
  - Web-based raster editor: https://www.photopea.com/
  - No installation required
  - Used for basic raster image editing and comparison with vector files

![Photopea Interface](../../../images/week-2/photopea-interface.jpg)

- **Affinity**
  - Downloaded from: https://affinity.serif.com/
  - Installed on Windows
  - Supports both raster and vector workflows

### 3D CAD Software
- **Fusion 360**
  - Access provided through Fab Academy
  - Downloaded from: https://www.autodesk.com/products/fusion-360
  - Installed using the Windows installer

![Fusion 360 Install](../../../images/week-2/fusion360-install.jpg)

- **SolidWorks**
  - Access provided through Fab Academy Makers / Makerspace license
  - Installed using the 3DEXPERIENCE Launcher:
    https://www.3ds.com/3dexperience
  - Followed the SolidWorks installation manager steps

![SolidWorks 3DEXPERIENCE](../../../images/week-2/solidworks-3dexperience.jpg)

- **Blender**
  - Downloaded from: https://www.blender.org/download/
  - Installed using the Windows installer
  - Used for non-parametric 3D modeling and visualization

![Blender Install](../../../images/week-2/blender-install.jpg)

- **OpenSCAD**
  - Downloaded from: https://openscad.org/downloads.html
  - Installed using the Windows installer
  - Used for script-based, parametric 3D modeling

![OpenSCAD Install](../../../images/week-2/openscad-1.jpg)

### Media Compression
- **HandBrake**
  - Downloaded from: https://handbrake.fr/
  - Installed on Windows
  - Used to compress videos before uploading to the Fab Academy site

![HandBrake Interface](../../../images/week-2/handbrake-interface.jpg)

---


## 2D Designing

### Vector Design – Inkscape

I started my 2D design exploration with **Inkscape**, focusing on vector-based workflows.  
As a fun and relatable exercise, I decided to create a **meme related to Formula 1**, specifically referencing **Lewis Hamilton, Ferrari, and their race strategy**.

I downloaded a few reference images from the internet and experimented with:
- **Trace Bitmap**
- Adjusting thresholds
- Cleaning up paths and nodes

This helped me understand how raster images can be converted into vectors and how editable paths behave in a vector environment.

**Inkscape Meme Output:**

<img src="../../../images/week-2/inkscape-meme.jpg" alt="Inkscape Meme" style="max-width: 100%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); margin: 20px 0;">

---

### Raster Design – Photopea

Next, I moved on to exploring raster graphics using **Photopea**.  
Since I had some prior experience with Photopea, it felt intuitive and easy to work with.

I recreated the **same meme** using raster tools to clearly understand the difference between:
- Pixel-based editing
- Resolution dependency
- Raster manipulation workflows

This exercise helped me directly compare raster vs vector approaches for the same design.

**Photopea Meme Output:**

<img src="../../../images/week-2/photopea-meme.jpg" alt="Photopea Meme" style="max-width: 100%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); margin: 20px 0;">

---


## 2D Designing Using Affinity

For my 2D design workflow using **Affinity**, I decided to start with a precise sketch created in **Fusion 360** and then refine and stylize it inside Affinity.

---

### Creating the Base Sketch in Fusion 360

I began by sketching a **bike model** using the **Fusion 360 sketch tools**.  
This allowed me to create clean, dimensionally accurate geometry before moving to a 2D design environment.

Once the sketch was complete, I exported it as a **DXF file** for use in Affinity.

**Fusion 360 Sketch Export:**  
![Affinity DXF Import](../../../images/week-2/affinity-1.jpg)

---

### Importing the DXF into Affinity

I then opened **Affinity** and imported the DXF file:

- Opened Affinity  
![Affinity Open](../../../images/week-2/affinity-2.jpg)

- Navigated to **File → Open**
- Selected the DXF file exported from Fusion 360

**DXF Import into Affinity:**  
![Affinity Import Step 1](../../../images/week-2/affinity-3.jpg)
![Affinity Import Step 2](../../../images/week-2/affinity-4.jpg)

After importing, I repositioned the geometry and **mirrored the DXF** to achieve the required orientation.

**Mirroring and Positioning the DXF:**  
![Affinity Mirroring](../../../images/week-2/affinity-5.jpg)

---

### Building Shapes and Cleaning Geometry

With the DXF correctly positioned, I used the **Shape Builder Tool** to:
- Combine required regions
- Remove unnecessary construction lines
- Convert raw sketch geometry into clean, closed shapes

This step helped transform the technical sketch into a usable 2D design.

**Shape Building and Cleanup:**  
![Affinity Shape Builder](../../../images/week-2/affinity-6.jpg)

---

### Applying Colors

Finally, I applied colors to the required areas to improve visual clarity and presentation.  
This step helped finalize the 2D render and made the design more readable and visually appealing.

**Final Colored Output:**  
![Affinity Final Color](../../../images/week-2/affinity-7.jpg)

---

## 3D Designing

This week, I explored **3D design** using multiple tools to understand different modeling philosophies:
- Parametric modeling
- Non-parametric / direct modeling
- Sculpting-based workflows  

The focus was not just on *making shapes*, but on understanding **how different tools think**.

---

## Fusion 360 – Parametric Modeling (Comfort Zone)

I started with **Fusion 360**, since I am already familiar with the software.  
This allowed me to focus on **design intent** rather than learning a new interface (low friction, high productivity).

**Workflow followed:**
- Created a **sketch on the Front Plane** in the **first quadrant**
- Used simple constraints to define the profile

![Fusion 360 Sketch](../../../images/week-2/fusion-1.jpg)

- Applied the **Revolve** tool to generate the main bowl-like body capable of holding liquid

![Fusion 360 Revolve](../../../images/week-2/fusion-2.jpg)

- Created a second sketch on the **Front Plane** for the **cup handle path**

![Fusion 360 Handle Path](../../../images/week-2/fusion-3.jpg)

- Used the **Pipe** tool to create a fully solid handle
- Rendered the final model to achieve a **glass-like appearance**

![Fusion 360 Final Render](../../../images/week-2/fusion-final.jpg)

**What I took away:**
- Parametric modeling is extremely powerful when design intent is clear
- Small sketch changes can update the entire model chef’s kiss 🤌
---
## Tea Cup Modeling Video Tutorial

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/Fusion-Cup.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

### This video demonstrates the complete workflow for modeling a tea cup in Fusion 360, from initial sketch to final rendering.


---

## Static Structural Analysis in Fusion 360

Before fabricating any physical parts, it's crucial to validate the design's structural integrity. **Static Structural Analysis** (also known as Finite Element Analysis or FEA) helps simulate how a part will behave under real-world loads and forces.

**Key Benefits of Static Structural Analysis:**
- **Identify Weak Points** – Find areas prone to stress concentration before manufacturing
- **Optimize Material Usage** – Reduce weight while maintaining strength
- **Predict Failure Modes** – Understand how and where a part might fail
- **Save Time & Cost** – Catch design flaws digitally instead of through physical testing

In Fusion 360, I ran a structural simulation on a L shaped cast iron piece to analyze stress distribution and displacement under load.

#### Structural Simulation Video

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/fusion-simulation.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

#### This video showcases the process of setting up and running a static structural analysis in Fusion 360, demonstrating how to evaluate stress and displacement in a designed part.
---
## 3D Designing Using Tinkercad

Next, I explored **Tinkercad**, a tool I am already familiar with.  
It is the same platform I previously used to introduce my **niece and nephews to 3D modelling**, where we created **keychains with their names** and had them 3D printed.

---

### Accessing Tinkercad

- Opened the Tinkercad website: https://www.tinkercad.com/
- Logged in and navigated to **Designs**
- Selected **Create → 3D Design**

![Tinkercad Interface](../../../images/week-2/tinkercad-1.jpg)

---

### Creating the Cup Body

- Dragged and dropped a **solid cylinder** onto the workspace
- Adjusted its dimensions to form the **outer body** of the cup

![Cup Body Creation](../../../images/week-2/tinkercad-2.jpg)

---

### Creating the Hollow Cavity

- Added a **hollow cylinder**
- Positioned it inside the solid cylinder
- Planned the placement such that performing a **boolean operation** would create a hollow cavity

---

### Creating the Handle

- Added **two additional cylinders**
- Rotated and positioned them to form the **handle** of the cup

![Cup Handle Creation](../../../images/week-2/tinkercad-3.jpg)

---

### Boolean Operation and Final Model

- Used the **Group** feature in Tinkercad (boolean operation)
- Combined and subtracted the shapes as required

The final cup model was obtained as shown below.

![Final Cup Model](../../../images/week-2/tinkercad-4.jpg)

---

## 3D Designing Using Onshape

I also explored **Onshape**, a cloud-based parametric CAD tool.  
Access to Onshape was provided through **Fab Academy**.

---

### Accessing Onshape

- Opened the Fab Academy Onshape portal:  
  https://fab.onshape.com/
- Logged in using the Fab Academy–provided access
- Created a **new document**

![Onshape Portal Access](../../../images/week-2/onshape-1.jpg)

---

### Creating a New Document

- Named the document according to my requirement

![Creating New Document](../../../images/week-2/onshape-2.jpg)

---

### Starting a Sketch

- Selected the **Sketch** tool

![Sketch Tool Selection](../../../images/week-2/onshape-3.jpg)

- Chose the **Front Plane** as the sketch plane

![Front Plane Selection](../../../images/week-2/onshape-4.jpg)

---

### Sketching the Cup Profile

- Drew the sketch required for creating the **hollow portion of the cup**
- This sketch was designed specifically for a **revolve operation**

![Cup Profile Sketch](../../../images/week-2/onshape-5.jpg)

---

### Revolve Operation

- Used the **Revolve** tool to generate the 3D cup body from the sketch

![Revolve Operation](../../../images/week-2/onshape-6.jpg)

---

### Creating the Handle

- Sketched a **circular profile**
- Defined a **path** for sweeping the handle
- Used the **Sweep** tool to create the cup handle

---

### Final Model

The final cup model was obtained after completing the revolve and sweep operations.

![Final OnShape Cup Model](../../../images/week-2/onshape-7.jpg)

---

## 3D Designing Using 3D Builder

**3D Builder** is another 3D CAD software I was already familiar with.  
It comes bundled with **Windows**, making it quick to access and easy to experiment with basic solid modeling workflows.

---

### Creating a Model in 3D Builder

- Opened **3D Builder**
- Selected **New Scene**

![3D Builder Opening](../../../images/week-2/3Dbuilder-1.jpg)

---

### Creating the Cup Body

- Created a **cylinder** to form the outer body of the cup

![3D Builder Cylinder](../../../images/week-2/3Dbuilder-2.jpg)

- Created another **cylinder**
- Scaled it down so it could be subtracted from the first cylinder
- Positioned it inside the outer cylinder to create a **hollow cup**

![3D Builder Hollow Cup Step 1](../../../images/week-2/3Dbuilder-3.jpg)
![3D Builder Hollow Cup Step 2](../../../images/week-2/3Dbuilder-4.jpg)

---

### Creating the Handle

- Imported two additional cylinders
- Rotated and positioned them appropriately to form the **handle shape**

![3D Builder Handle](../../../images/week-2/3Dbuilder-5.jpg)

---

### Boolean Operations and Final Model

- Used **subtract** and **merge** operations
- Combined all components to generate the final cup model

![3D Builder Final Model](../../../images/week-2/3Dbuilder-6.jpg)

---

## 3D Designing Using OpenSCAD

To explore **script-based parametric modeling**, I used **OpenSCAD**, where geometry is created using code rather than a graphical interface.

---

### Opening OpenSCAD

- Opened **OpenSCAD** after installation

![OpenSCAD Interface](../../../images/week-2/openscad-1.jpg)

---

### Creating the Model Using Code

I created the required code to generate a **simple cylindrical coffee mug** with a handle.  
The code was generated with the help of **ChatGPT**.

#### ChatGPT Prompt Used

```text
Write OpenSCAD code to create a simple cylindrical coffee mug that is hollow inside.

- Height: 90 mm
- Outer radius: 35 mm
- Wall thickness: about 5 mm
- Include a curved side handle
```
### OpenSCAD Code

The following OpenSCAD script was used to create a **simple cylindrical coffee mug** with a hollow body and a curved handle.

```scad
// -------- TORUS (HANDLE SHAPE) MODULE --------
module torus(R, r) {
    rotate_extrude($fn=120)
        translate([R, 0, 0])
            circle(r=r, $fn=60);
}

// -------- COMPLETE MUG (BODY + HANDLE) --------
union() {

    // ---- HOLLOW MUG BODY ----
    difference() {
        // Outer shell
        cylinder(h = 90, r = 35, $fn=120);

        // Inner hollow space
        translate([0,0,3])
            cylinder(h = 84, r = 30, $fn=120);
    }

    // ---- HANDLE ----
    translate([35, 0, 30])
    rotate([90,0,0])
        torus(15, 5);
}
```
### Rendering the Model

The model was rendered in OpenSCAD using the **Render** function.

![OpenSCAD Rendered Mug](../../../images/week-2/openscad-3.jpg)


## Blender – Non-Parametric Modeling (Out of Comfort Zone)

Blender was a completely different vibe.

Coming from engineering CAD tools like Fusion 360, SolidWorks, Siemens NX, CATIA, Creo, and Onshape, Blender initially felt:
- Non-linear
- Less constraint-driven
- More artistic than engineering-focused  

Basically, I was a **fish out of water**, but in a good way.

#### First Exercise: Water Bottle on a Table

**Steps followed:**
- Inserted a **cylinder** and extruded it to the required height
- Used the **Bevel** tool with high segment count to round off the top and bottom
- Created a second cylinder for the **bottle cap**
- Applied bevels to give it a realistic look

![Blender Bottle](../../../images/week-2/blender-bottle.jpg)

**Creating the table:**
- Inserted a cube and scaled it to form the tabletop
- Added four cubes to act as table legs

![Blender Bottle and Table](../../../images/week-2/blender-bottle-and-table.jpg)

At this stage, my brain was officially **fried** for the day 💀.

---

### Blender Sculpting – Where It Got Fun

Later that evening, I discussed Blender sculpting workflows with my close friend **Adhityan SV** and his brother **Aryan SV**, who has significant experience working with Blender.

🔗 **Reference:**  
https://www.linkedin.com/in/adithyansv/

https://aryansv807.artstation.com/projects

They introduced me to:
- Sculpt Mode
- Basic sculpting brushes
- Organic modeling workflows  

Inspired by this (and slightly distracted by someone playing **Clash of Clans** next to me), I decided to sculpt a **Goblin head** — just the head.

**Sculpting process:**
- Started with a **sphere** as the base mesh

![Blender Goblin Base](../../../images/week-2/blender-goblin-1.jpg)

- Used sculpting brushes to define facial features
- Focused on form rather than precision

![Blender Goblin Progress](../../../images/week-2/blender-goblin-2.jpg)

![Blender Goblin Final](../../../images/week-2/blender-goblin-3.jpg)

**Why this was a W:**
- Extremely intuitive and hands-on
- Felt like working with **play-dough**
- Brought back childhood creativity
- Zero stress, maximum fun (10/10 would sculpt again)

#### Bird Head Sculpting Video Tutorial

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/Blender.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

This video shows the sculpting process of creating a rough bird head in Blender, demonstrating the organic and intuitive nature of the sculpting workflow.


---

## SolidWorks – Back to Home Base

The final CAD tool I worked with this week was **SolidWorks**, which is my primary and most comfortable CAD software.

After experimenting with Blender, returning to SolidWorks felt:
- Structured
- Predictable
- Very much *home*

**Strategic Plan for Final Project:**
- **Fusion 360** will be used for the **initial concept and rough renders** of my final project
- **SolidWorks** will be the primary tool for the **full engineering CAD** and detailed design iterations
- This hybrid approach leverages Fusion's quick prototyping with SolidWorks' precision engineering capabilities

#### Tea Cup Modeling Video Tutorial

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/Solidworks.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

This video demonstrates the complete workflow for modeling a tea cup in SolidWorks, showcasing the structured and predictable approach of this powerful CAD tool.

---

### Final Project Concept – Rough Render (Fusion 360)

This week, I created the first visual representation of my final project concept in Fusion 360. This rough render serves as a proof-of-concept for the design direction I'm planning to pursue throughout Fab Academy.

**Project Concept:** Smart Toolbox (Advanced version with embedded intelligence and tracking)

The rough render demonstrates:
- Overall form factor and ergonomics
- General spatial layout of components
- Visual direction for the final design

#### Final Project Rough Render Video

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/fusion-final-project-render.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

This video showcases the initial concept render of the Smart Toolbox, giving a visual preview of the design direction for my final project.

#### Toolbox Render Images

<img src="../../../images/week-2/tool_box_render_2026-Feb-02_09-22-25PM-000_CustomizedView24430321981_jpg.jpg" alt="Toolbox Render View 1" style="max-width: 100%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); margin: 15px 0;">

<img src="../../../images/week-2/tool_box_render_2026-Feb-02_09-22-48PM-000_CustomizedView10744737428_jpg.jpg" alt="Toolbox Render View 2" style="max-width: 100%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); margin: 15px 0;">

<img src="../../../images/week-2/tool_box_render_2026-Feb-02_09-23-23PM-000_CustomizedView2223318742_jpg.jpg" alt="Toolbox Render View 3" style="max-width: 100%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); margin: 15px 0;">

These renders show different angles of the Smart Toolbox concept, highlighting the overall design aesthetic and component layout.

*(Final project renders and engineering details will be documented as the project progresses through upcoming weeks.)*

---
## Image and Video Compression

Since Fab Academy has strict limits on image and video sizes, I paid attention to compressing all media files before uploading them to the documentation page.

---

### Image Compression (Windows)

For image compression, I used the **Image Resizer** option available in the **Windows Photos app**.

**Workflow:**
- Open the image using the **Windows Photos** app
- Click on the **Image Resizer** option
- Adjust the resolution and size parameters to reduce file size
- Ensure the image meets Fab Academy size requirements before saving

<div style="display: flex; gap: 20px; justify-content: center; flex-wrap: wrap; margin: 20px 0;">
  <img src="../../../images/week-2/image-resize-1.jpg" alt="Image Resize Step 1" style="max-width: 45%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <img src="../../../images/week-2/image-resize-2.jpg" alt="Image Resize Step 2" style="max-width: 45%; height: auto; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
</div>

This method was quick and effective for reducing image sizes without noticeably affecting quality.

---

### Video Compression (HandBrake)

For video compression, I used **HandBrake** to meet the Fab Academy guideline of approximately **1 MB per minute**.

**Workflow:**
- Open HandBrake
- Import the video file
- Select appropriate resolution and compression settings
- Export the compressed video file

#### Video Compression Tutorial

<div style="max-width: 100%; margin: 20px 0; border-radius: 8px; overflow: hidden; box-shadow: 0 4px 12px rgba(0,0,0,0.15);">
  <video autoplay loop width="100%" height="auto" controls style="display: block;">
    <source src="/images/week-2/videos/Handbrake.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</div>

This video demonstrates the complete workflow for compressing videos in HandBrake, showing how to achieve the optimal balance between file size and quality.

HandBrake allowed me to significantly reduce video file sizes while keeping the content clear and usable for documentation.

---



## Reflections

This week helped me build a strong foundation in understanding **how design files are created and prepared for fabrication**.  
I learned the clear difference between raster and vector graphics, explored multiple 3D tools, and realized the importance of choosing the right software for the right purpose.

------

