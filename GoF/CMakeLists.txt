#first we add the executable that generates the table
add_executable(MakeTable MakeTable.cpp)

#add the command to generate source code
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable)

#add the binary directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add the main library
add_library (GoF mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/Table.h maze.cpp mazegame.cpp)

target_include_directories(GoF
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
    ${PROJECT_SOURCE_DIR}/GoF
    )

target_compile_features(GoF PRIVATE cxx_override)

install (TARGETS GoF DESTINATION bin)
