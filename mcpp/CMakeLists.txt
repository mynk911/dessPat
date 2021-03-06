cmake_minimum_required(VERSION 3.5)
project(MCPP VERSION 0.1 LANGUAGES CXX)

add_library(mcpp INTERFACE)
add_library(MCPP::mcpp ALIAS mcpp)

target_sources(mcpp
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mcpp.hpp>
    )

target_include_directories(mcpp
    INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/MCPP>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    )

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MCPP)

install(
    TARGETS
        mcpp
    EXPORT
        MCPPTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT MCPPTargets
    FILE MCPPTargets.cmake
    NAMESPACE MCPP::
    DESTINATION ${INSTALL_CONFIGDIR}
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MCPP
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mcpp_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MCPP
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MCPPConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/MCPPConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/MCPPConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/MCPPConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/MCPPConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(mcpp_doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif(DOXYGEN_FOUND)
endif()

