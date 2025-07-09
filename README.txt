SIMCITY – POLLUTION & HAPPINESS SIMULATION

This is a simulation-based city planning project created in C++ as a Data Structures & Algorithms assignment at the University of North Texas.
It reads a configuration file and region layout to simulate pollution, wind, and how they affect residential happiness and growth.

--------------------------------------------------------------------------------
WHAT IT DOES:

• Loads a region layout and configuration from input files ("conf.txt" and "region.csv").
• Simulates the growth and development of different cell types (residential, commercial, etc.).
• Models pollution levels in each cell and their effects on neighboring areas.
• Allows the user to specify a wind direction, which spreads pollution across the grid over time.
• Tracks happiness levels in residential zones based on pollution exposure.
• Residents will stop moving in when happiness falls too low, and move out if pollution improves.

--------------------------------------------------------------------------------
HOW HAPPINESS & POLLUTION WORK:

• Each residential cell starts with full happiness (100).
• For every 1 unit of pollution added to a residential cell, happiness decreases by 20 points.
• Pollution spreads one cell per timestep in the wind’s direction, if the source cell's pollution > 2.
• Once happiness drops below 50, new residents stop arriving.
• If pollution drops below 20, a resident moves out and a worker is removed from either the available worker pool or a commercial cell.
• From a user-specified direction, wind will blow pollution in that direction every timestep, increasing all adjacent cells facing that direction by 1. 

--------------------------------------------------------------------------------
ANALYSIS TOOLS:

At the end of the simulation, you can choose from four analysis outputs:

- Analyze Rectangular Area → Based on user-provided coordinates inside the city-grid, data will be output for that area.
- Print Pollution  → Displays the pollution level of each cell in the region.
- Print Happiness  → Displays happiness values for all residential cells only.
- Quit → Exits the program.

--------------------------------------------------------------------------------
HOW TO RUN:

1. Download the project folder and open it in the CELL server environment.
2. Compile the program:

   Option 1 – Using Make:
       make

   Option 2 – Manual compilation:
       g++ *.cpp -o SimCity

3. Run the simulation:
       ./SimCity

4. Follow the program prompts:
   - You'll be prompted for the name of the conf.txt file
   - You’ll be asked to enter a wind direction (N, S, E, or W).
   - The simulation will run timestep by timestep, simulating growth and environmental changes.

--------------------------------------------------------------------------------
FILE DESCRIPTIONS:

• conf.txt      → Configuration for the simulation (e.g. growth parameters).
• region.csv    → Layout of the region to simulate (e.g. cell types and placement).
• SimCity       → Compiled executable after building.
• *.cpp, *.h    → Source code files for the simulation engine.

You may replace "conf.txt" and "region.csv" with your own files using the same format.

--------------------------------------------------------------------------------
ERROR CODES:

Code 2 → The program was unable to open "region.csv".

--------------------------------------------------------------------------------
CONTACT:

Created by Cade Medearis  
Email: cademedearis@gmail.com
LinkedIn: https://www.linkedin.com/in/cademedearis/

--------------------------------------------------------------------------------
HOW TO TRY IT:

If you're reviewing this project:

1. Compile with "make" or "g++ *.cpp -o SimCity".
2. Run the program with "./SimCity".
3. Try different wind directions and observe how pollution and happiness evolve.
4. Use the Analyze options to analyze your results.

(Option to do "make clean" to remove the executable and .o files)