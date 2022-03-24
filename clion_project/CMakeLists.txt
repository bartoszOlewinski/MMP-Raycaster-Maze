cmake_minimum_required(VERSION 3.20)
project(Raycaster)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SFML_DIR "${PROJECT_SOURCE_DIR}/resources/SFMLv15_64/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics audio REQUIRED)


set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/resources/libtorch/share/cmake/Torch")
find_package(Torch REQUIRED)
include_directories(SYSTEM ${TORCH_INCLUDE_DIRS})


add_executable(Raycaster src/game/main.cpp src/graphics/Raycaster.h src/graphics/Raycaster.cpp src/game/Actor.cpp src/game/Actor.h
        src/game/DebugConsole.cpp src/game/Sprite.cpp src/game/Sprite.h src/game/Map.cpp src/game/Map.h src/graphics/Menu.cpp src/graphics/Menu.h
        src/game/GameSetup.cpp src/game/GameSetup.h src/game/Controller.cpp src/game/Controller.h src/torch/Agent.cpp src/torch/Agent.h)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio "${TORCH_LIBRARIES}")

#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif (MSVC)

