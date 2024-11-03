# Whack-A-Mole Game Development Guide

This guide explains how to create a simple "Whack-A-Mole" game using the **JepGo Engine**. The project demonstrates how to set up a basic game structure, manage assets, and use components and systems within the JepGo ecosystem.

## Project Structure

The project structure is organized as follows:

```
samples/whack-a-mole/
├── assets
│   ├── background.png
│   └── sprite-mole.png
├── CMakeLists.txt
├── components
│   └── Score.hpp
├── game.client.cpp
├── include
│   └── Global.hpp
├── systems
│   ├── HandleMoleBehaviorSystem.cpp
│   └── ScoreSystem.cpp
└── whack-a-mole-game
```

### Key Files
- **assets/**: Contains the game assets, such as background and mole sprite images.
- **components/**: Includes custom game components, such as `Score.hpp` to manage game scoring.
- **systems/**: Contains game logic systems, like `HandleMoleBehaviorSystem.cpp` and `ScoreSystem.cpp`.
- **Global.hpp**: Defines constants and enums specific to the Whack-A-Mole game.
- **game.client.cpp**: The main game file that sets up the game environment, loads assets, and defines core functions for creating game entities.

## Getting Started

To get started with development:

1. **Set Up the Project Environment**
   - Ensure you have JepGo Engine set up on your development environment.
   - Use `CMakeLists.txt` to configure the build.

2. **Compile and Run**
   - Use `cmake` to generate the build system and compile:
     ```bash
     mkdir build && cd build
     cmake ..
     make
     ```
   - Run the game executable:
     ```bash
     ./whack-a-mole-game
     ```

### Explanation of CMakeLists.txt

In this project, **CMake** is used to manage the build configuration and generation. The `CMakeLists.txt` file defines compilation options, libraries, dependencies, and the build process for various game components of the "Whack-A-Mole" game.

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi
```

This line sets the minimum required version of CMake (here 3.14) for building the project, ensuring compatibility with specific CMake features used in the script.

```cmake
SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
```

These lines set the C++ standard to be used (C++23 in this case) and enforce it as mandatory for the project.

#### Defining Game Systems

The following section lists the source files for game systems located in the `systems/` folder, such as `HandleMoleBehaviorSystem.cpp` and `ScoreSystem.cpp`:

```cmake
SET(Systems
    systems/HandleMoleBehaviorSystem.cpp
    systems/ScoreSystem.cpp
)
```

These files contain the logic for each game system and are dynamically added using a `foreach` loop that iterates over each listed file.

#### Loop to Add Each System

For each system source file:

```cmake
foreach(file ${Systems})
    get_filename_component(basename ${file} NAME_WLE)
    string(CONCAT finalName "jepgo.system." ${basename})
    project(${finalName})
    message(${finalName})
    add_library(${finalName} SHARED ${file})
```

1. `get_filename_component` extracts the file’s name without the extension.
2. `string(CONCAT ...)` concatenates a prefix ("jepgo.system.") with this base name to create a unique project name.
3. `project(${finalName})` initializes the project for each system.
4. `add_library` creates a shared library for each system, which is used for dynamic loading within the engine.

Additional commands set up include and link directories for each system library using `TARGET_INCLUDE_DIRECTORIES` and `TARGET_LINK_DIRECTORIES`. A `ADD_CUSTOM_COMMAND` then copies each built library to the output directory.

#### Main Executable Configuration

The main game executable is defined as follows:

```cmake
PROJECT(whack-a-mole-game)
ADD_EXECUTABLE(whack-a-mole-game game.client.cpp)
```

- `PROJECT` defines the project name.
- `ADD_EXECUTABLE` adds the executable `whack-a-mole-game`, built from `game.client.cpp`, the main entry point of the game.

Additional configuration commands define include directories, link directories, and required libraries (`jepengine` and `jepmod`) for the executable.

Finally, a custom command copies the executable to the output folder.

#### Summary

This `CMakeLists.txt` file configures each system as a dynamic library, manages dependencies, and builds the main executable. This setup allows for modularity and dynamic loading of game components based on the project structure.

## Game Mechanics

### Main Functions

- **`onStart`**: Initializes the game by loading assets, creating game entities, and configuring components.
- **`onUpdate`**: Updates the game state in real-time.

### Entity Creation Functions

- **`createBackground`**: Adds a static background to the game.
- **`createMole`**: Creates and places a mole entity on the screen with clickable and animated properties.
- **`createScore`**: Adds a score display that updates based on player actions.

### Example: Creating the Background

```cpp
static void createBackground(jgo::Client &game)
{
    game.ecs.createEntity();
    game.ecs.emplaceComp<Positions>(game.ecs.currentEntity, Positions(0, 0));
    game.ecs.emplaceComp<Drawable>(game.ecs.currentEntity, Drawable(WhackAMole::TEXTURES_PATH.at(WhackAMole::GAME_BACKGROUND), jgo::Rectangle(0, 50, 800, 600)));
}
```

### Game Components

- **Score**: A custom component to manage player scores.
  ```cpp
  class Score {
      public:
          Score(std::string const &title, long int const &score = 0) : _title(title), _score(score) {};
          ...
  };
  ```
- **Sprite2DMultiAnim**: Manages the mole's animation states, allowing it to change appearance based on its state.

### Game Systems

- **ScoreSystem**: Updates and renders the player’s score.
- **HandleMoleBehaviorSystem**: Controls mole behavior, changing states based on game events (e.g., clicked, missed, or hit by bomb).

### Core Gameplay Logic

- **Mole Behavior**: Defined in `MOLE_BEHAVIOR`, where each tuple specifies a set of behaviors and transitions.
- **Score Updates**: Moles react based on interactions. For instance, hitting a mole increases the score, while hitting a bomb decreases it.

### Example: Defining Mole Behavior

Each mole state is defined by specific animations and timing:
```cpp
const std::map<int, std::vector<jgo::Vector2>> MOLES_ANIM = {
    {(int)MoleStates::SLEEP, {{3, 7}}},
    {(int)MoleStates::WAKE_UP, {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}},
    ...
};
```

## Adding New Features

To extend this game, you can:
- **Add More Animations**: Extend `MOLES_ANIM` to add new animations or behaviors.
- **Custom Score Handling**: Modify `ScoreSystem` to add combos or multiplier mechanics.
- **Enhance Graphics**: Add new textures or effects to enhance visuals.

## Conclusion

The **Whack-A-Mole** game serves as an example of creating interactive games with the JepGo Engine, showcasing entity-component-system (ECS) design, modular systems, and component-based animations. By following this guide, you should be able to expand this game further or use the structure as a base for other projects.


