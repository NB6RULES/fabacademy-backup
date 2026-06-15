+++
title = "Week 17 - Wildcard Week"
weight = 117
bookCollapseSection = true
+++

# Week 17 - Wildcard Week

Week 17 is **wildcard week**, an opportunity to explore a fabrication process or technology not covered in the regular curriculum.  
The aim was to learn something new that could contribute to the final project or expand personal skills.

This week allows for creative exploration and learning beyond the standard Fab Academy topics.

---

## Assignment
- Design and produce something using a **fabrication process not covered** in another assignment

## Possible Topics
- **Composites** - fiber reinforcement, layup techniques
- **Textiles** - e-textiles, soft circuits, digital embroidery
- **Biocomposites** - natural materials, mycelium
- **Welding** - metal joining techniques
- **Vacuum forming** - advanced thermoforming
- **Other** - any process you want to explore

---

## What I Learned

This week I learned that you don't need fancy tools to make something cool. All you need is a phone camera, a piece of paper, and a good idea. Using Tool Trace to turn pictures of my tools into outlines was way easier than I thought, and it saved me a lot of time compared to drawing everything by hand. I also learned how a waterjet machine works, which was really cool. I didn't know water could cut through tough stuff like metal just by shooting out super fast with some sand mixed in. Doing a test cut first also taught me why it's smart to check your settings before the real cut. It helps you catch mistakes early instead of messing up your final piece.

---

## Software Used
- **Process-specific software**
- **Design software** as needed
- **Browser + Git** for documentation

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Wildcard week introduction |
| THU | Planned the task for the week and decided to make foam tool cutouts for my drawer |
| FRI | Found Tool Trace, took photos of my tools, and made the SVG design |
| SAT | Learned about the different parts of the waterjet machine |
| SUN | Got the file ready in the Omax software and made the tool paths |
| MON | Did a test cut, then cut the final foam tool holder |
| TUE | Regional review |

---

This week, I wanted to do something connected to my final project. I thought about it and decided to make tool cutouts for my drawer, cut out of foam. I talked to my instructors about it, and they said using the waterjet to cut foam would be a good idea. So that's what I planned to do this week. Let's get started.

First, I needed to make the designs for the tool cutouts.

Instead of drawing and scaling everything by hand, I found a tool called [tooltrace.ai](https://tooltrace.ai).

![image](../../../images/week-17/00.jpg)

Here's how it works:
- You take a picture of your tools next to an A4 or letter-size sheet of paper.
- The sheet is used as a size guide.
- Tool Trace then creates a scaled outline of each tool.
- You can use that outline to cut it out, 3D print it, or do whatever you want with it.

My first step was to figure out and list all the tools I wanted to add.

I walked around the lab, found a bunch of tools, made a list, and laid them all out next to an A4 sheet. I took a picture of that, and used Tool Trace to turn it into an SVG outline.

![image](../../../images/week-17/01.jpg)

![image](../../../images/week-17/02.jpg)

After that, I downloaded the file and went to cut it on the waterjet.

## Using Tool Trace

- **Step 1:** Import the image into Tool Trace.

![image](../../../images/week-17/2.jpg)

- **Step 2:** Add finger notches to the design so the tools can be easily lifted out of the foam.

![image](../../../images/week-17/3.jpg)

- **Step 3:** Wait for the finger joint preview to finish loading.

![image](../../../images/week-17/4.jpg)

- **Step 4:** Download the SVG file.

![image](../../../images/week-17/5.jpg)

- **Step 5:** Set the scale to millimeters (mm).

![image](../../../images/week-17/6.jpg)

## Learning the Parts of the Waterjet Machine

The machine in our lab is an **OMAX 5555**. It's basically a giant cutting table that uses a super thin stream of water mixed with garnet (a type of sand) to slice through almost anything — metal, foam, plastic, stone, you name it. The water shoots out so fast and so hard that it can cut through tough materials without using any heat, so the material doesn't melt or get damaged. It's controlled by a computer, so you just feed it your design file and it cuts it out exactly the way you drew it.

- Water storage tank for the waterjet machine
![wildcard](../../../images/week-17/wildcard-1.jpg)

- Reverse osmosis (RO) water filter system for the machine
![wildcard](../../../images/week-17/wildcard-2.jpg)

- Water chiller for the machine
![wildcard](../../../images/week-17/wildcard-3.jpg)

- The interactive control panel
![wildcard](../../../images/week-17/wildcard-7.jpg)

- The power switch
![wildcard](../../../images/week-17/wildcard-10.jpg)

- Water pressure and temperature gauges and controls
![wildcard](../../../images/week-17/wildcard-11.jpg)

- Emergency stop button and water level adjuster
![wildcard](../../../images/week-17/wildcard-16.jpg)

- Water filter pressure gauges (before and after the filter) — these two numbers should match for the waterjet to work properly
![wildcard](../../../images/week-17/wildcard-19.jpg)

- The water pump, which makes the huge pressure needed to create the water jet
![wildcard](../../../images/week-17/wildcard-21.jpg)
![wildcard](../../../images/week-17/wildcard-23.jpg)
![wildcard](../../../images/week-17/wildcard-24.jpg)

- The water pump's model number
![wildcard](../../../images/week-17/wildcard-25.jpg)
![wildcard](../../../images/week-17/wildcard-29.jpg)
![wildcard](../../../images/week-17/wildcard-30.jpg)

## Getting the File Ready for Waterjet Cutting

- **Open the Omax Layout software** and import the SVG file made with Tool Trace.

![wildcard](../../../images/week-17/wildcard-32.jpg)
![wildcard](../../../images/week-17/wildcard-33.jpg)
![wildcard](../../../images/week-17/wildcard-34.jpg)
![wildcard](../../../images/week-17/wildcard-35.jpg)
![wildcard](../../../images/week-17/wildcard-36.jpg)

- **Check the scale factor** and make sure it's set to 1.

![wildcard](../../../images/week-17/wildcard-37.jpg)
![wildcard](../../../images/week-17/wildcard-38.jpg)
![wildcard](../../../images/week-17/wildcard-39.jpg)
![wildcard](../../../images/week-17/wildcard-40.jpg)

- **Generate the tool path.**

![wildcard](../../../images/week-17/wildcard-42.jpg)
![wildcard](../../../images/week-17/wildcard-43.jpg)
![wildcard](../../../images/week-17/wildcard-44.jpg)
![wildcard](../../../images/week-17/wildcard-46.jpg)
![wildcard](../../../images/week-17/wildcard-47.jpg)

- **Zoom in on the tool path** and check that the pierce points line up with the right spots on the foam.

![wildcard](../../../images/week-17/wildcard-48.jpg)
![wildcard](../../../images/week-17/wildcard-49.jpg)
![wildcard](../../../images/week-17/wildcard-50.jpg)
![wildcard](../../../images/week-17/wildcard-51.jpg)

- **Export the tool path** so it's ready for the final cut.

![wildcard](../../../images/week-17/wildcard-52.jpg)

- **Pick the material type and thickness** for the cut.

![wildcard](../../../images/week-17/wildcard-53.jpg)
![wildcard](../../../images/week-17/wildcard-55.jpg)
![wildcard](../../../images/week-17/wildcard-57.jpg)
![wildcard](../../../images/week-17/wildcard-58.jpg)

- **Use the built-in nesting feature** to arrange copies of each cutout shape so they fit neatly together.

![wildcard](../../../images/week-17/wildcard-59.jpg)
![wildcard](../../../images/week-17/wildcard-60.jpg)
![wildcard](../../../images/week-17/wildcard-63.jpg)
![wildcard](../../../images/week-17/wildcard-64.jpg)
![wildcard](../../../images/week-17/wildcard-65.jpg)
![wildcard](../../../images/week-17/wildcard-66.jpg)

- **Try a test cut** to check the settings and the quality of the cut.

![wildcard](../../../images/week-17/wildcard-67.jpg)

- **Set the machine to low pressure** for the test cut.

![wildcard](../../../images/week-17/wildcard-68.jpg)
![wildcard](../../../images/week-17/wildcard-69.jpg)
![wildcard](../../../images/week-17/wildcard-70.jpg)
![wildcard](../../../images/week-17/wildcard-71.jpg)

## Setting the Origin and Starting the Cut

![wildcard](../../../images/week-17/wildcard-72.jpg)
![wildcard](../../../images/week-17/wildcard-73.jpg)
![wildcard](../../../images/week-17/wildcard-74.jpg)
![wildcard](../../../images/week-17/wildcard-75.jpg)
![wildcard](../../../images/week-17/wildcard-77.jpg)
![wildcard](../../../images/week-17/wildcard-78.jpg)

<video controls width="100%" style="max-width: 600px; margin: 20px 0;">
  <source src="../../../images/week-17/wildcard.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

## Hero Shots
![image](../../../images/week-17/001.jpg)
![image](../../../images/week-17/002.jpg)
![image](../../../images/week-17/003.jpg)

---