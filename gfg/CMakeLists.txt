#add the main library
add_library (gfg gfg.c)
target_include_directories(gfg
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
    ${PROJECT_SOURCE_DIR}/gfg
    )

install (TARGETS gfg DESTINATION bin)
