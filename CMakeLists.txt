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

    # engine.scene
    source/engine/scene/Scene.cpp
    source/engine/scene/Scene.h
    
    # engine.entity
    source/engine/entity/GameObject.cpp
    source/engine/entity/GameObject.h

    source/engine/entity/dummy/Poly.cpp
    source/engine/entity/dummy/Poly.h
    
    # engine.component
    source/engine/component/Component.cpp
    source/engine/component/Component.h

    # engine.component.collider
    source/engine/component/collider/ColliderComponent.cpp
    source/engine/component/collider/ColliderComponent.h

    # engine.component.drawable
    source/engine/component/drawable/DrawComponent.cpp
    source/engine/component/drawable/DrawComponent.h

    source/engine/component/drawable/DrawPolygonComponent.cpp
    source/engine/component/drawable/DrawPolygonComponent.h

    # engine.component.rigidbody
    source/engine/component/rigidbody/RigidBodyComponent.cpp
    source/engine/component/rigidbody/RigidBodyComponent.h

    source/engine/component/rigidbody/RigidBody2DComponent.cpp
    source/engine/component/rigidbody/RigidBody2DComponent.h

    # engine.utils
    source/engine/utils/Math.cpp
    source/engine/utils/Math.h

    source/engine/utils/Transform.h

    # engine.utils.builder
    source/engine/utils/builder/Builder.h
    source/engine/utils/builder/Director.h
)

# Link SDL
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})