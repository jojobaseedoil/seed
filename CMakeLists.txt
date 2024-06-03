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
    
    # engine.component
    source/engine/component/Component.cpp
    source/engine/component/Component.h

    # engine.component.collider
    source/engine/component/Collider.cpp
    source/engine/component/Collider.h

    source/engine/component/BoxCollider.cpp
    source/engine/component/BoxCollider.h
    
    # engine.component.drawable
    source/engine/component/Render.cpp
    source/engine/component/Render.h

    source/engine/component/Sprite.cpp
    source/engine/component/Sprite.h

    # engine.component.rigidbody
    source/engine/component/RigidBody.cpp
    source/engine/component/RigidBody.h

    # engine.component.monobehaviour
    source/engine/component/MonoBehaviour.cpp
    source/engine/component/MonoBehaviour.h

    # engine.system.collisionsystem
    source/engine/system/CollisionSystem.cpp
    source/engine/system/CollisionSystem.h
    
    # engine.utils
    source/engine/utils/Math.cpp
    source/engine/utils/Math.h

    # engine.utils.idmanager
    source/engine/utils/IDManager.cpp
    source/engine/utils/IDManager.h

    # engine.utils.eventmanager
    source/engine/utils/EventManager.cpp
    source/engine/utils/EventManager.h

    # engine.utils.builder
    source/engine/utils/builder/Builder.h
    source/engine/utils/builder/Director.h

    # engine.utils.observer
    # source/engine/utils/observer/Observer.cpp
    # source/engine/utils/observer/Observer.h
)

# Link SDL
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -lSDL2_image)