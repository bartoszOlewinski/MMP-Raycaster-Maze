cmake_minimum_required(VERSION 3.20)
project(Raycaster)

set(CMAKE_CXX_STANDARD 14)

# put SFML library in /resources folder, must be 32bit
set(SFML_DIR "${PROJECT_SOURCE_DIR}/resources/SFML32/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics audio REQUIRED)

# add paths to your python installations, must be 3.10 32bits
set(PYTHON_INCLUDE_DIR "C:/Users/barto/AppData/Local/Programs/Python/Python310-32/include")
set(PYTHON_LIBRARY "C:/Users/barto/AppData/Local/Programs/Python/Python310-32/libs/python310.lib")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})



add_executable(Raycaster src/game/main.cpp src/graphics/Raycaster.h src/graphics/Raycaster.cpp src/game/Actor.cpp src/game/Actor.h
        src/game/Sprite.cpp src/game/Sprite.h src/game/Map.cpp src/game/Map.h src/graphics/Menu.cpp src/graphics/Menu.h
        src/game/GameSetup.cpp src/game/GameSetup.h src/game/Controller.cpp src/game/Controller.h src/torch/PythonRunner.cpp src/torch/PythonRunner.h)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio ${PYTHON_LIBRARIES})

