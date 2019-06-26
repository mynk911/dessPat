cmake_minimum_required(VERSION 3.12) 
project(common VERSION 1.0 LANGUAGES C) 

add_library (common OBJECT include/c_utils.h
  c_utils/c_utils.c )

target_include_directories(common
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

