cmake_minimum_required(VERSION 3.15)
project(Nibler)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

find_package(PkgConfig REQUIRED)

include_directories(./core/inc
                    ./sfml/inc
                    ./sdl/inc
                    ./CinLib/inc
                    .CinLib/Cinder/include/cinder
                    )

add_executable(Nibler
        ./core/inc/Game.h
        core/inc/GUI.h
        core/inc/Snake.h
        sfml/inc/SFML.h
        sdl/inc/SDLLIB.h
        core/src/Game.cpp
        core/src/main.cpp
        sfml/src/SFML.cpp
        sdl/src/SDLLIB.cpp
        core/src/Snake.cpp
        CinLib/src/CINLIB.cpp
        CinLib/inc/CINLIB.h)
target_link_libraries(Nibler sfml-graphics sfml-audio)