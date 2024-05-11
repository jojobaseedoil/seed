cmake_minimum_required(VERSION 3.22.1)

# Set the project name
project(seed)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Including SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add an executable
add_executable(
    ${PROJECT_NAME} 
    
    # main entry
    source/main.cpp
    
    # engine.game
    source/engine/game/Game.cpp
    source/engine/game/Game.h
)

# Link SDL
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})