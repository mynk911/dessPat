cmake_minimum_required(VERSION 3.5)
project(LIN VERSION 0.1 LANGUAGES CXX)

add_library(lin src/lin.cpp
                include/lin.h)
add_library(LIN::lin ALIAS lin)

include(GenerateExportHeader)
generate_export_header(lin)
target_include_directories(lin
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/LIN>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/LIN)

install(
    TARGETS
        lin
    EXPORT
        LINTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT LINTargets
    FILE LINTargets.cmake
    NAMESPACE LIN::
    DESTINATION ${INSTALL_CONFIGDIR}
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LIN
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lin_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LIN
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LINConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/LINConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/LINConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/LINConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/LINConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if(BUILD_DOCS)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(lin_doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)

