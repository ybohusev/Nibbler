cmake_minimum_required(VERSION 3.14)
project(Nibler)

set(CMAKE_CXX_STANDARD 14)

#find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#find_package(PkgConfig REQUIRED)

include_directories(./core/inc
                    ./sfml/inc
                    ./sfml/sfml/SFML-2.5.0-macOS-clang/include
                    ./sdl/inc
                    ./ncurses/inc
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
        ncurses/inc/NCULIB.hpp
        ncurses/src/NCULIB.cpp)
#target_link_libraries(Nibler sfml-graphics sfml-audio)