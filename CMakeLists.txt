cmake_minimum_required (VERSION 2.6)
project (dessPat)

#The Version number
set (dessPat_VERSION_MAJOR 1)
set (dessPat_VERSION_MINOR 0)

#does the system provide LOG and EXP functions?
include(CheckCXXSymbolExists)
check_cxx_symbol_exists(log cmath HAVE_LOG)
check_cxx_symbol_exists(exp cmath HAVE_EXP)

#configure a header file to pass some of the cmake settings to the source code
configure_file (
 "${PROJECT_SOURCE_DIR}/dessPatConfig.h.in"
 "${PROJECT_BINARY_DIR}/dessPatConfig.h"
)

#add the binary directory to the search path for include files so that we will
#find dessPatConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#should we use lib GoF ?
option (GOF "use gang of four" ON)

#add the GoF library ?
if(GOF)
include_directories("${PROJECT_SOURCE_DIR}/GoF")
add_subdirectory (GoF)
set (EXTRA_LIBS ${EXTRA_LIBS} GoF)
endif(GOF)

#add the executable
add_executable (dessPat dessPat.cpp)
target_link_libraries (dessPat ${EXTRA_LIBS})

#add install targets
install (TARGETS dessPat DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/dessPatConfig.h" DESTINATION include)

include (CTest)

#does the application run
add_test(dessPatRuns dessPat 25)
#does it square root 25
add_test(dessPatComp25 dessPat 25)
set_tests_properties(dessPatComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
#does it handle negative numbers
add_test(dessPatNegative dessPat -25)
set_tests_properties(dessPatNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")
#does it handle small numbers
add_test(dessPatSmall dessPat 0.0001)
set_tests_properties(dessPatSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
#does the usage message work
add_test(dessPatUsage dessPat)
set_tests_properties(dessPatUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test (dessPatComp${arg} dessPat ${arg})
  set_tests_properties (dessPatComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# do a bunch of result based tests
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")

#build a CPack driven installer package
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/License.txt)
set(CPACK_PACKAGE_VERSTON_MAJOR ${dessPat_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${dessPat_VERSION_MINOR})
include(CPack)


