# Python Game - C++ Port

This is a C++ port of the original Python game using Allegro 5 as the graphics library instead of Pygame.

## Prerequisites

You need to have the following installed on your system:

### macOS
```bash
# Install Allegro 5 using Homebrew
brew install allegro5

# Install CMake if not already installed
brew install cmake
```

### Ubuntu/Debian
```bash
# Install Allegro 5 development libraries
sudo apt-get install liballegro5-dev liballegro5.2

# Install CMake if not already installed
sudo apt-get install cmake
```

### Windows
- Download and install Allegro 5 from: https://github.com/liballeg/allegro5/releases
- Install CMake from: https://cmake.org/download/

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Configure the project with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Running the Game

After building, run the game:
```bash
./game_cpp
```

## Controls

- **WASD**: Move the player (up, left, down, right)
- **I/O**: Zoom in/out
- **ESC**: Toggle pause menu
- **Mouse**: Click menu options in pause menu
- **Arrow Keys**: Navigate pause menu
- **Enter**: Select menu option

## Project Structure

- `main.cpp`: Main game loop and initialization
- `displayed_map.h/cpp`: Map display and zoom functionality
- `file_extraction.h/cpp`: File reading utilities
- `menus.h/cpp`: Pause menu implementation
- `moving.h/cpp`: Player movement logic
- `player.h/cpp`: Player class and rendering
- `CMakeLists.txt`: Build configuration
- `maps/`: Map files (same as Python version)

## Differences from Python Version

1. **Graphics Library**: Uses Allegro 5 instead of Pygame
2. **Event Handling**: Uses Allegro's event system
3. **Memory Management**: Manual memory management for C++ objects
4. **Build System**: Uses CMake for cross-platform building

The game logic and functionality remain the same as the original Python version. 