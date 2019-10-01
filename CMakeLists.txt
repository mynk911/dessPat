cmake_minimum_required (VERSION 3.12)
project (dessPat)

#use CXX 17 (for gcc)
set (CMAKE_CXX_STANDARD 17)
#The Version number
set (dessPat_VERSION_MAJOR 0)
set (dessPat_VERSION_MINOR 1)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

option(BUILD_SHARED_LIBS "build shared library instead of static" OFF)

#Control unit tests which use service mocking as explained here.
#https://www.codeproject.com/Articles/1040972/Using-GoogleTest-and-GoogleMock-frameworks-for-emb
#The method is a bit experimental and has issues in shared lib builds.
option(C_SERVICE_MOCK_TESTS "use service mocking tests for c projects.
    (experimental)" OFF)
mark_as_advanced(C_SERVICE_MOCK_TESTS)

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
find_package(Doxygen)
endif()

find_package(Boost)
find_package(Threads)

add_subdirectory(common)

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

if(UNIX)
add_subdirectory (lin)
find_package(Curses REQUIRED)
set (EXTRA_LIBS ${EXTRA_LIBS} LIN::lin)
set( SRC_FILES ${SRC_FILES} tests/lin/tests_lin.cpp)
endif(UNIX)

if(WIN32)
add_subdirectory (win)
set (EXTRA_LIBS ${EXTRA_LIBS} WIN::win)
set( SRC_FILES ${SRC_FILES} tests/win/tests_win.cpp)
endif(WIN32)

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

set( SRC_FILES ${SRC_FILES} dessPat.cpp
			    tests/concur/tests_concur.cpp
			    tests/cs180/tests_cs180.cpp
			    tests/gfg/test_gfg.cpp
			    tests/gof/tests_gof.cpp
			    tests/lcthw/tests_lcthw.cpp
			    tests/mcpp/tests_mcpp.cpp)

if(C_SERVICE_MOCK_TESTS)
    set( SRC_FILES ${SRC_FILES}
	tests/lcthw/ServicesMocks.h
	tests/lcthw/FakeServices.h)
endif(C_SERVICE_MOCK_TESTS)
#add the executable
add_executable (dessPat ${SRC_FILES})

#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
target_include_directories(dessPat
    PUBLIC
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/tests
    PRIVATE
    ${PROJECT_BINARY_DIR})
target_link_libraries (dessPat ${EXTRA_LIBS} gmock)
