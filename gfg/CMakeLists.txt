#add the main library
add_library (gfg gfg.c)
target_include_directories(gfg
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gfg
    )
#target_compile_features(gfg PRIVATE c_std_11)

set_property(TARGET GoF PROPERTY C_STANDARD 11)
set_property(TARGET GoF PROPERTY C_STANDARD_REQUIRED ON)
install (TARGETS gfg DESTINATION bin)
