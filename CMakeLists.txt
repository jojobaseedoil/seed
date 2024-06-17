cmake_minimum_required(VERSION 3.22.1)

# Set the project name
project(seed)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Defining main directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(ENGINE_COMPONENT_DIR ${SOURCE_DIR}/engine/component)
set(ENGINE_GAME_DIR ${SOURCE_DIR}/engine/game)
set(ENGINE_SCENE_DIR ${SOURCE_DIR}/engine/scene)
set(ENGINE_ENTITY_DIR ${SOURCE_DIR}/engine/entity)
set(ENGINE_SYSTEM_DIR ${SOURCE_DIR}/engine/system)
set(ENGINE_UTILS_DIR ${SOURCE_DIR}/engine/utils)

# find packages with pkg-config
include(FindPkgConfig)

# Find the necessary packages
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

# Print out the package information for debugging
message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

message(STATUS "SDL2_image include dirs: ${SDL2IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_image libraries: ${SDL2IMAGE_LIBRARIES}")

message(STATUS "SDL2_ttf include dirs: ${SDL2TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf libraries: ${SDL2TTF_LIBRARIES}")

message(STATUS "SDL2_mixer include dirs: ${SDL2MIXER_INCLUDE_DIRS}")
message(STATUS "SDL2_mixer libraries: ${SDL2MIXER_LIBRARIES}")

# Including dirs
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})
include_directories(${SDL2MIXER_INCLUDE_DIRS})

# Add an executable
add_executable(
    ${PROJECT_NAME} 
    ${SOURCE_DIR}/main.cpp
    ${ENGINE_GAME_DIR}/Game.cpp
    ${ENGINE_SCENE_DIR}/Scene.cpp
    ${ENGINE_ENTITY_DIR}/GameObject.cpp
    ${ENGINE_COMPONENT_DIR}/Component.cpp
    ${ENGINE_COMPONENT_DIR}/Collider.cpp
    ${ENGINE_COMPONENT_DIR}/BoxCollider.cpp
    ${ENGINE_COMPONENT_DIR}/Render.cpp
    ${ENGINE_COMPONENT_DIR}/Sprite.cpp
    ${ENGINE_COMPONENT_DIR}/RigidBody.cpp
    ${ENGINE_COMPONENT_DIR}/MonoBehaviour.cpp
    ${ENGINE_COMPONENT_DIR}/Text.cpp
    ${ENGINE_SYSTEM_DIR}/collision/CollisionSystem.cpp
    ${ENGINE_SYSTEM_DIR}/input/InputSystem.cpp
    ${ENGINE_SYSTEM_DIR}/input/InputDevice.cpp
    ${ENGINE_SYSTEM_DIR}/input/Keyboard.cpp
    ${ENGINE_SYSTEM_DIR}/sound/AudioSystem.cpp
    ${ENGINE_UTILS_DIR}/Math.cpp
    ${ENGINE_UTILS_DIR}/SceneManager.cpp

    source/engine/prefab/PrefabText.cpp
)

# Link SDL
target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
    ${SDL2IMAGE_LIBRARIES} 
    ${SDL2TTF_LIBRARIES} 
    ${SDL2MIXER_LIBRARIES}
)