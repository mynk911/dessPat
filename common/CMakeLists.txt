cmake_minimum_required(VERSION 3.12) 
project(common VERSION 1.0 LANGUAGES C) 

add_library (common OBJECT include/c_utils.h
                           include/bstrlib.h
                           c_utils/c_utils.c
                           c_utils/bstrlib.c)

# On linux, common is build without -fPIC by default and this causes linking to fail
# common is linked to shared objects.
# on windows the below check is not required.
if(BUILD_SHARED_LIBS)
 set_property(TARGET common PROPERTY POSITION_INDEPENDENT_CODE ON) 
endif(BUILD_SHARED_LIBS)

target_include_directories(common
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

