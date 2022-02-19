cmake_minimum_required(VERSION 3.20)
project(Raycaster)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "${PROJECT_SOURCE_DIR}/resources/SFML32/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(Raycaster src/game/main.cpp src/graphics/Raycaster.h src/graphics/Raycaster.cpp src/game/Actor.cpp src/game/Actor.h
        src/game/MapHandler.h src/game/MapHandler.cpp src/game/DebugConsole.cpp src/game/Sprite.cpp src/game/Sprite.h)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
