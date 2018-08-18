cmake_minimum_required(VERSION 3.5) 
project(CS180 VERSION 1.0 LANGUAGES CXX) 

add_library(cs180 src/cs180.cpp)

target_include_directories(cs180
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
