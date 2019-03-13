cmake_minimum_required(VERSION 3.5) 
project(LCTHW VERSION 1.0 LANGUAGES C) 

add_library (lcthw include/lcthw.h
				   src/ex1.c
				   src/ex3.c
				   src/ex7.c
				   src/ex16.c
				   src/ex17.c
				   src/ex18.c
				   src/ex19.c
				   src/ex22.c
				   src/ex22_m.c
				   src/ex23.c
				   src/ex24.c
				   src/ex25.c)
add_library (LCTHW::lcthw ALIAS lcthw)
include(GenerateExportHeader)
generate_export_header(lcthw)
target_include_directories(lcthw
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/LCTHW>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(UNIX)
target_compile_features(lcthw
    PUBLIC c_restrict
    )
endif(UNIX)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/LCTHW)

install(
    TARGETS
        lcthw
    EXPORT
        LCTHWTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT LCTHWTargets
    FILE LCTHWTargets.cmake
    NAMESPACE LCTHW::
    DESTINATION ${INSTALL_CONFIGDIR} 
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LCTHW
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lcthw_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LCTHW
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LCTHWConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/LCTHWConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/LCTHWConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/LCTHWConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/LCTHWConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(lcthw_doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif(DOXYGEN_FOUND)
endif()
