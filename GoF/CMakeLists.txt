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
add_library (GoF mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install (TARGETS GoF DESTINATION bin)
install (FILES gof.h DESTINATION include)
