cmake_minimum_required(VERSION 3.5) 
project(Geek VERSION 1.0 LANGUAGES C) 

add_library (gfg src/gfg.c)

target_include_directories(gfg
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(UNIX)
target_compile_features(gfg
    PUBLIC c_restrict
    )
endif(UNIX)
