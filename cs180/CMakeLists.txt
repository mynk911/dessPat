cmake_minimum_required(VERSION 3.5) 
project(CS180 VERSION 1.0 LANGUAGES CXX) 

add_library (cs180 src/cs180.cpp)
add_library (CS180::cs180 ALIAS cs180)
include(GenerateExportHeader)
generate_export_header(cs180)
target_include_directories(cs180
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CS180>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_compile_features(cs180
    PUBLIC cxx_override
    )

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/CS180)

install(
    TARGETS
        cs180
    EXPORT
        CS180Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT CS180Targets
    FILE CS180Targets.cmake
    NAMESPACE CS180::
    DESTINATION ${INSTALL_CONFIGDIR} 
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CS180
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cs180_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CS180
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/CS180ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/CS180Config.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/CS180Config.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/CS180Config.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/CS180ConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if(BUILD_DOCS)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(cs180_doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)
