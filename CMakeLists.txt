cmake_minimum_required (VERSION 3.5)
project (dessPat)

#use CXX 14 (for gcc)
set (CMAKE_CXX_STANDARD 14)
#The Version number
set (dessPat_VERSION_MAJOR 0)
set (dessPat_VERSION_MINOR 1)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

option(BUILD_SHARED_LIBS "build shared library instead of static" OFF)

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
find_package(Doxygen)
endif()

find_package(Boost)
find_package(Threads)

if(Boost_FOUND)
add_subdirectory (GoF)
set (EXTRA_LIBS ${EXTRA_LIBS} GOF::gof)
endif(Boost_FOUND)

if(Threads_FOUND)
add_subdirectory (concur)
set (EXTRA_LIBS ${EXTRA_LIBS} CONCUR::concur)
endif(Threads_FOUND)

add_subdirectory (mcpp)
set (EXTRA_LIBS ${EXTRA_LIBS} MCPP::mcpp)
add_subdirectory (lin)
set (EXTRA_LIBS ${EXTRA_LIBS} LIN::lin)
add_subdirectory (win)
set (EXTRA_LIBS ${EXTRA_LIBS} WIN::win)
add_subdirectory (gfg)
set (EXTRA_LIBS ${EXTRA_LIBS} GFG::gfg)
add_subdirectory(lcthw)
set (EXTRA_LIBS ${EXTRA_LIBS} LCTHW::lcthw)
add_subdirectory (cs180)
set (EXTRA_LIBS ${EXTRA_LIBS} CS180::cs180)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# Replace install() to do-nothing macro.
macro(install)
endmacro()

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# Restore original install() behavior.
macro(install)
  _install(${ARGN})
endmacro()

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

#add the executable
add_executable (dessPat dessPat.cpp
                        tests/gfg/test_gfg.cpp
                        tests/lcthw/tests_lcthw.cpp
                        tests/lcthw/ServicesMocks.h
                        tests/lcthw/ServicesMocks.cpp
                        tests/lcthw/Fixture.h
                        tests/lcthw/Fixture.cpp
                        tests/lcthw/FakeServices.cpp
                        tests/lcthw/FakeServices.h)

#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
target_include_directories(dessPat
    PUBLIC
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/tests
    PRIVATE
    ${PROJECT_BINARY_DIR})
target_link_libraries (dessPat ${EXTRA_LIBS} gmock)
