cmake_minimum_required(VERSION 4.0.2)
project(MavRendszer)

set(CMAKE_CXX_STANDARD 20)

add_executable(MavRendszer main.cpp
        Vonat.cpp
        Vonat.h
        Szemelyvonat.cpp
        Szemelyvonat.h
        InterCity.cpp
        InterCity.h
        Jegy.cpp
        Jegy.h
        KedvezmenyesJegy.cpp
        KedvezmenyesJegy.h
        TeljesAruJegy.cpp
        TeljesAruJegy.h
        MavRendszer.cpp
        MavRendszer.h)
