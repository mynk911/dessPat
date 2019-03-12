cmake_minimum_required (VERSION 3.5)
project (dessPat)

#use CXX 14 (for gcc)
set (CMAKE_CXX_STANDARD 14)
#The Version number
set (dessPat_VERSION_MAJOR 1)
set (dessPat_VERSION_MINOR 0)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

#configure sample input file
configure_file (
 "${PROJECT_SOURCE_DIR}/sampleInput.txt.in"
 "${PROJECT_BINARY_DIR}/sampleInput.txt"
 COPYONLY
)

option(BUILD_SHARED_LIBS "build shared library instead of static" OFF)
option(BUILD_DOCS "build documentation on" ON )

if(BUILD_DOCS)
find_package(Doxygen)
if(DOXYGEN_FOUND)
   message("doxygen found")
else(DOXYGEN_FOUND)
   message("doxygen not found")
endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)

#optional lib 
option (GOF "use gang of four" ON)
option (GFG "use geek" ON)
option (LCTHW "use hard" ON)
option(CS180 "use cs180" ON)
option(CONCUR "use concur" ON)
option(MCPP "use mcpp" ON)
option(LIN "use lin" ON)
option(WIN "use win" ON)

#add the GoF library ?
if(GOF)
add_subdirectory (GoF)
set (EXTRA_LIBS ${EXTRA_LIBS} GOF::gof)
endif(GOF)

#add the gfg library ?
if(GFG)
add_subdirectory (gfg)
set (EXTRA_LIBS ${EXTRA_LIBS} GFG::gfg)
endif(GFG)

#add the lcthw library ?
if(LCTHW)
add_subdirectory(lcthw)
set (EXTRA_LIBS ${EXTRA_LIBS} LCTHW::lcthw)
endif(LCTHW)

#add the cs180 library ?
if(CS180)
add_subdirectory (cs180)
set (EXTRA_LIBS ${EXTRA_LIBS} CS180::cs180)
endif(CS180)

#add the concur library ?
if(CONCUR)
add_subdirectory (concur)
set (EXTRA_LIBS ${EXTRA_LIBS} CONCUR::concur)
endif(CONCUR)

#add the mcpp library ?
if(MCPP)
add_subdirectory (mcpp)
set (EXTRA_LIBS ${EXTRA_LIBS} MCPP::mcpp)
endif(MCPP)

#add the lin library ?
if(LIN)
add_subdirectory (lin)
set (EXTRA_LIBS ${EXTRA_LIBS} LIN::lin)
endif(LIN)

#add the win library ?
if(WIN)
add_subdirectory (win)
set (EXTRA_LIBS ${EXTRA_LIBS} WIN::win)
endif(WIN)

#add the executable
add_executable (dessPat dessPat.cpp)
#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
target_include_directories(dessPat
    PUBLIC
    ${CMAKE_SOURCE_DIR}/common/include
    PRIVATE
    ${PROJECT_BINARY_DIR})
target_link_libraries (dessPat ${EXTRA_LIBS})
