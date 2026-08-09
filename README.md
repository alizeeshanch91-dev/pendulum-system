Double Pendulum Chaos Simulator

A double pendulum simulation I built in C++ using raylib. A double pendulum is just a pendulum with another pendulum attached to the end of it, and even though the physics behind it is fully deterministic, the motion looks completely random and chaotic. Small changes in the starting angle lead to totally different outcomes over time — that's the whole point of this project.

WHAT IT DOES
- Renders two connected pendulum arms with bobs at each joint
- Uses the real double pendulum equations of motion, not a simplified version
- Updates the physics every frame using semi-implicit Euler integration
- Lets you press SPACE to spawn a second pendulum that starts almost identical to the first (just a tiny difference in starting angle) so you can literally watch chaos happen — they swing together for a bit, then diverge completely
- Shows live stats on screen: current angle, angular velocity, gravity value
- Asks you at startup to type in a starting angular velocity (between -10 and 10), and won't let you continue until you type something valid

CONTROLS
SPACE - spawns the second pendulum
ESC or close window - quits

HOW TO BUILD IT
You need Visual Studio and raylib. I didn't use vcpkg, so I linked raylib manually:
1. Clone the repo and open it in Visual Studio
2. Go to Project Properties
3. Under C/C++ > General > Additional Include Directories, add raylib's include folder
4. Under Linker > General > Additional Library Directories, add raylib's lib folder
5. Under Linker > Input > Additional Dependencies, add: raylib.lib;winmm.lib;gdi32.lib;user32.lib;shell32.lib;
6. Build and run

No std::vector or STL containers anywhere in this project, just plain structs, classes, and raw arrays.

FILES
main.cpp - opens the window, runs the game loop, handles the startup input
Arm.h / Arm.cpp - holds one arm's data: angle, angular velocity, length, mass
Pendulum.h / Pendulum.cpp - owns two arms plus the pivot point, runs the physics and draws everything

HOW THE PHYSICS WORKS
Each arm keeps track of its angle, angular velocity, length, and mass. The angular acceleration isn't stored anywhere — it gets recalculated fresh every single frame based on the current angles and velocities of BOTH arms, because the two arms are coupled. Arm two's motion literally pulls back on arm one through the joint connecting them, and that back-and-forth interaction is exactly what makes the whole system chaotic instead of just being two normal pendulums stuck together.

Every frame, update() does this:
1. Grabs the current angle, velocity, length, and mass for both arms
2. Plugs them into the acceleration equations (these come from Lagrangian mechanics, I didn't derive them by hand, just implemented them)
3. Updates velocity first using the new acceleration, then updates angle using the new velocity — this order matters, it's called semi-implicit Euler and it's more stable than doing it the other way around

The actual equations, if you want to see them:

theta1 acceleration = (A + B + C) divided by L1 times (2*m1 + m2 - m2*cos(2*delta))
  A = gravity pulling arm 1 down, plain and simple
  B = a second gravity effect caused by arm 2 hanging off arm 1
  C = arm 2's current motion physically tugging on arm 1

theta2 acceleration = 2*sin(delta) times (D + E + F), divided by L2 times (2*m1 + m2 - m2*cos(2*delta))
  D = arm 1's motion driving arm 2
  E = gravity transmitted through arm 1's angle
  F = arm 2's own momentum feeding back on itself

where delta is just theta1 minus theta2, basically how bent the two arms currently are relative to each other.

RAYLIB FUNCTIONS I USED
InitWindow(width, height, title) - opens the window, call once at the start
SetTargetFPS(60) - caps the frame rate
WindowShouldClose() - true once you close the window, used to control the main loop
GetFrameTime() - gives you the time since the last frame, I use this as dt
BeginDrawing() / EndDrawing() - everything you want to draw goes between these two
ClearBackground(color) - wipes the screen before drawing the next frame
DrawLine(x1, y1, x2, y2, color) - used for the pendulum arms
DrawCircle(x, y, radius, color) - used for the pivot and the bobs
DrawText(text, x, y, fontsize, color) - used for all the on screen stats
TextFormat("label: %.2f", value) - works like printf, lets you drop a number into a string for DrawText
IsKeyPressed(KEY_SPACE) - fires true for one frame when you press a key, used for spawning the second pendulum
CloseWindow() - cleans up the window at the end

OTHER RAYLIB FUNCTIONS THAT COULD BE USEFUL LATER
Fade(color, amount) - fades a color out, good if I ever add the trail effect back in
IsKeyDown(key) - true for as long as a key is held down, not just one press
GetMousePosition() - could let you drag the pivot around with the mouse
MeasureText(text, size) - tells you how wide a string will be on screen, useful for lining text up properly
DrawRectangle(x, y, w, h, color) - could put a background box behind the stats text so it's easier to read

WHAT I LEARNED
Turning a set of coupled differential equations into actual working code, one term at a time.
Why semi-implicit Euler is more stable than plain Euler for something that oscillates.
How to structure a multi file C++ project properly with headers and implementation files, without leaning on the STL.
Working with raylib for the first time, including the window loop, drawing shapes and text, and reading keyboard input.
And a lot of debugging practice — chasing bugs back to their actual root cause instead of guessing, like uninitialized memory,
reading a variable before it's assigned, and a stray system("cls") call that was quietly killing performance every frame.
