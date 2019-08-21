cmake_minimum_required(VERSION 3.12)
project(LCTHW VERSION 0.1 LANGUAGES C)

add_library (lcthw include/lcthw.h src/lcthw.c $<TARGET_OBJECTS:common>)
add_library (LCTHW::lcthw ALIAS lcthw)

include(GenerateExportHeader)
generate_export_header(lcthw)
target_include_directories(lcthw
PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/LCTHW>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
PRIVATE
    $<TARGET_PROPERTY:common,INCLUDE_DIRECTORIES>
    )

if(C_SERVICE_MOCK_TESTS)
target_include_directories(lcthw
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests/lcthw>
    )
endif(C_SERVICE_MOCK_TESTS)

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
