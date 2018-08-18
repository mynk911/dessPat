cmake_minimum_required(VERSION 3.5) 
project(GoF VERSION 1.0 LANGUAGES CXX) 

add_library (GoF src/maze.cpp src/mazegame.cpp src/maze.h)

target_include_directories(GoF
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_compile_features(GoF
    PUBLIC cxx_override
    )
