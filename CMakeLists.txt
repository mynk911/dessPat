cmake_minimum_required (VERSION 3.5)
project (dessPat)

#use C11 (for gcc)
set (CMAKE_CXX_STANDARD 11)
#The Version number
set (dessPat_VERSION_MAJOR 1)
set (dessPat_VERSION_MINOR 0)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

#configure saple input file
configure_file (
 "${PROJECT_SOURCE_DIR}/sampleInput.txt.in"
 "${PROJECT_BINARY_DIR}/sampleInput.txt"
 COPYONLY
)

#optional lib 
option (GOF "use gang of four" ON)
option (GFG "use geek" ON)
option (LCTHW "use hard" ON)
option(CS180 "use cs180" ON)

#add the GoF library ?
if(GOF)
add_subdirectory (GoF)
set (EXTRA_LIBS ${EXTRA_LIBS} GoF)
endif(GOF)

#add the gfg library ?
if(GFG)
add_subdirectory (gfg)
set (EXTRA_LIBS ${EXTRA_LIBS} GFG::gfg)
endif(GFG)

#add the lcthw library ?
if(LCTHW)
add_subdirectory(lcthw)
set (EXTRA_LIBS ${EXTRA_LIBS} lcthw)
endif(LCTHW)

#add the cs180 library ?
if(CS180)
add_subdirectory (cs180)
set (EXTRA_LIBS ${EXTRA_LIBS} cs180)
endif(CS180)

#add the executable
add_executable (dessPat dessPat.cpp)
#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
target_include_directories(dessPat 
PRIVATE ${PROJECT_BINARY_DIR})
target_link_libraries (dessPat ${EXTRA_LIBS})
