#add the main library
add_library (lcthw src/ex1.c src/ex3.c)

target_include_directories(lcthw
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(UNIX)
target_compile_features(lcthw
    PUBLIC c_restrict
    )
end(UNIX)   
