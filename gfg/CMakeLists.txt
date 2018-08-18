cmake_minimum_required(VERSION 3.5) 
project(GFG VERSION 1.0 LANGUAGES C) 

add_library (gfg src/gfg.c)
add_library (GFG::gfg ALIAS gfg)
target_include_directories(gfg
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gfg>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(UNIX)
target_compile_features(gfg
    PUBLIC c_restrict
    )
endif(UNIX)


include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/GFG)

install(
    TARGETS
        gfg
    EXPORT
        GFGTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSRALL_BINDIR}
    )

install(EXPORT GFGTargets
    FILE GFGTargets.cmake
    NAMESPACE GFG::
    DESTINATION ${INSTALL_CONFIGDIR} 
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GFG
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/GFGConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/GFGConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/GFGConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/GFGConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/GFGConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )
