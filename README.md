# 2D Game

A simple 2D game built with C++ and Allegro 5, featuring procedurally generated maps and player movement.

## Features

- **Procedural Map Generation**: Uses Perlin noise to generate terrain maps
- **Player Movement**: WASD controls for character movement
- **Pause Menu**: ESC key to pause/unpause the game
- **Map Display**: Visual representation of the generated terrain

## Prerequisites

- **CMake** (version 3.10 or higher)
- **Allegro 5** library
- **C++17** compatible compiler
- **Python** (for map generation)

### Installing Allegro 5 on macOS

```bash
brew install allegro
```

## Building the Project

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd 2D-Game
   ```

2. **Build the project**
   ```bash
   ./build.sh
   ```

   Or manually:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Running the Game

After building, run the game:

```bash
./build/game_cpp
```

## Controls

- **W/A/S/D**: Move player (up/left/down/right)
- **ESC**: Pause/unpause game
- **Close window**: Exit game

## Map Generation

Generate new maps using the Python script:

```bash
python map_generation.py
```

This creates new map files in the `maps/` directory.

## Project Structure

```
├── main.cpp              # Main game loop
├── player.cpp/h          # Player class and movement
├── displayed_map.cpp/h   # Map rendering
├── menus.cpp/h           # Pause menu system
├── moving.cpp/h          # Movement logic
├── file_extraction.cpp/h # File I/O utilities
├── map_generation.py     # Procedural map generation
├── build.sh              # Build script
└── CMakeLists.txt        # CMake configuration
```

## Clean Build

To start fresh, simply delete the `build/` folder and rebuild:

```bash
rm -rf build
./build.sh
```
