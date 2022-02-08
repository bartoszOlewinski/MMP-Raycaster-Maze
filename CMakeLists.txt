cmake_minimum_required(VERSION 3.16)
project(mmpPrototype)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR ${PROJECT_SOURCE_DIR}/resources/SFML32/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(mmpPrototype src/game/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)