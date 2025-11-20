# Interactive-Space-Exploration-2D-Solar-System-Visualization

A fully interactive, educational 2D Solar System simulation designed with C++, OpenGL, and FreeGLUT.

## Overview

This project offers a visually rich and smooth animated model of the solar system in two dimensions. It features interactive screens for space exploration, floating stars, animated clouds, planetary orbits, and educational pop-ups for every planet and the Sun. The design is ideal for learning, teaching, and visualizing the basics of our Solar System.

## Features

- **Intro Scene:** Animated background with twinkling stars, moving clouds, trees, a telescope, and a sky observer.
- **Interactive Transitions:** Click to advance from the introduction to the orbiting solar system.
- **2D Solar System Visualization:**
  - Realistic animated orbits for 9 planets (including Pluto) with unique rotation speeds and radii.
  - Colored and labeled planets, each with a clickable orbit.
  - Central Sun with vibrant coloring and custom information screen.
- **Educational Content:** Click a planet or the Sun to see facts such as diameter, surface features, atmospheric details, and other highlights. A fact box with a styled border appears for each.
- **Pause/Resume:** Animation can be paused and resumed.
- **Keyboard Controls:** Use arrow keys in the intro screen to tilt the telescope.
- **Stylized Design:** Smooth OpenGL drawing for orbits, planets, planet labels, a nebula background, and atmospheric stars.

## Dependencies

- **C++ Compiler** (supporting C++11 or greater)
- **OpenGL** and **GLUT/FreeGLUT** libraries

  - Example for Ubuntu:  
    ```
    sudo apt-get install freeglut3-dev
    ```
  - For Windows, install FreeGLUT and ensure the development libraries are in your project include/linker paths.

## Build and Run

1. **Clone the repository:**
   ```
   git clone https://github.com/A-T-I-K-A/Interactive-Space-Exploration-2D-Solar-System-Visualization
   cd Interactive-Space-Exploration-2D-Solar-System-Visualization
   ```

2. **Compile the code:**
   - Using `g++` (Linux/macOS):
     ```
     g++ main.cpp -o solar_system -lGL -lGLU -lglut
     ```
   - Using Visual Studio/Code::Blocks/DevC++ (Windows):  
     Ensure the project is linked with OpenGL32.lib, glut32.lib, and any other necessary libraries.

3. **Run the executable:**
   ```
   ./solar_system
   ```

## Controls

- **Arrow Keys (Intro screen):** Tilt telescope up or down.
- **Mouse Click (Intro):** Click the right half to enter the Solar System.
- **Mouse Click (Solar System):** Click a planet or the Sun to see detailed facts.
- **Mouse Click (Planet Info):** Click anywhere to return to Solar System view.
- **Other clicks:** Navigating between menus as described.

## File Structure

- `main.cpp` – Main simulation and interactive logic, rendering, and event handlers.
- `README.md` – This documentation.
- (Additional resource/config files as the project evolves.)

## Educational Content Source

Planet information is sourced and summarized for effective student learning.

## Screenshots and Demo

See the [project page](https://github.com/A-T-I-K-A/Interactive-Space-Exploration-2D-Solar-System-Visualization) for images, demos, and future updates.

## Contributing

Fork this repository to extend with new planets, moons, comet paths, 3D features, improved backgrounds, or translation/localization support. Pull requests welcome!

## License

This project is open-source. See `LICENSE` file for more details.

***

For latest updates, issues, and to fork the repository, visit:  
[Interactive-Space-Exploration-2D-Solar-System-Visualization](https://github.com/A-T-I-K-A/Interactive-Space-Exploration-2D-Solar-System-Visualization).[4]

[1](https://stackoverflow.com/questions/54089691/how-to-set-a-texture-as-background-in-opengl)
[2](https://community.khronos.org/t/to-create-rotate-a-star-shape-object/13542)
[3](https://github.com/topics/freeglut)
[4](https://labex.io/tutorials/cpp-creating-the-solar-system-in-opengl-298836)
[5](http://cfetch.blogspot.com/2014/06/wap-to-draw-star-in-opengl.html)
[6](https://github.com/lancelafontaine/opengl-final-project/blob/master/main.cpp)
[7](https://www.codeproject.com/articles/A-Star-Wars-Scroller-Demo-written-in-OpenGL-GLUT-u)
[8](https://www.scribd.com/document/425789111/03cgopen-1)
[9](https://www.youtube.com/watch?v=8Qkpaewj-7Y)
[10](https://github.com/ping543f/Computer-Graphics--OpenGL-GLUT/blob/master/BOAT_CLOUD_scene.cpp)
[11](https://www.reddit.com/r/cpp_questions/comments/5px5ii/creating_a_game_with_c_and_freeglut_opengl_need_a/)
[12](https://onecompiler.com/cpp/3y9sn4cz4)
[13](https://freeglut.sourceforge.net/docs/api.php)
[14](https://github.com/favia96/Solar-System_OpenGL/blob/master/solar_system.cpp)
[15](https://gist.github.com/Korayementality/f5f5d2e988385df66340)
[16](https://github.com/ping543f/Computer-Graphics--OpenGL-GLUT/blob/master/solar_system.cpp)
[17](http://cplussplussatplay.blogspot.com/2011/12/)
[18](https://onecompiler.com/cpp/3y9f4ncqw)
[19](https://onecompiler.com/cpp/3xk98g8ym)
