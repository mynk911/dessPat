cmake_minimum_required (VERSION 2.6)
project (dessPat)

#The Version number
set (dessPat_VERSION_MAJOR 1)
set (dessPat_VERSION_MINOR 0)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#add the executable
add_executable (dessPat dessPat.cpp)