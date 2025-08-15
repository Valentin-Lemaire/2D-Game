cmake_minimum_required(VERSION 3.10)
project(PythonGameCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Allegro 5
find_package(PkgConfig REQUIRED)

# Get Allegro libraries for include paths
pkg_check_modules(ALLEGRO_CORE REQUIRED allegro-5)
pkg_check_modules(ALLEGRO_MAIN REQUIRED allegro_main-5)
pkg_check_modules(ALLEGRO_FONT REQUIRED allegro_font-5)
pkg_check_modules(ALLEGRO_TTF REQUIRED allegro_ttf-5)
pkg_check_modules(ALLEGRO_PRIMITIVES REQUIRED allegro_primitives-5)

# Include directories
include_directories(${ALLEGRO_CORE_INCLUDE_DIRS})

# Add executable
add_executable(game_cpp
    main.cpp
    displayed_map.cpp
    file_extraction.cpp
    menus.cpp
    moving.cpp
    player.cpp
)

# Link libraries with full paths in correct order
target_link_libraries(game_cpp 
    /opt/homebrew/Cellar/allegro/5.2.10.1_1/lib/liballegro_main.5.2.10.dylib
    /opt/homebrew/Cellar/allegro/5.2.10.1_1/lib/liballegro.5.2.10.dylib
    /opt/homebrew/Cellar/allegro/5.2.10.1_1/lib/liballegro_font.5.2.10.dylib
    /opt/homebrew/Cellar/allegro/5.2.10.1_1/lib/liballegro_ttf.5.2.10.dylib
    /opt/homebrew/Cellar/allegro/5.2.10.1_1/lib/liballegro_primitives.5.2.10.dylib
) 