cmake_minimum_required(VERSION 3.5)
project(CONCUR VERSION 0.1 LANGUAGES CXX)

add_library(concur src/concur.cpp
                   include/concur.h)
add_library(CONCUR::concur ALIAS concur)

find_package(Threads)
target_link_libraries(concur ${CMAKE_THREAD_LIBS_INIT})

include(GenerateExportHeader)
generate_export_header(concur)
target_include_directories(concur
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CONCUR>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/CONCUR)

install(
    TARGETS
        concur
    EXPORT
        CONCURTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT CONCURTargets
    FILE CONCURTargets.cmake
    NAMESPACE CONCUR::
    DESTINATION ${INSTALL_CONFIGDIR}
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CONCUR
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/concur_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CONCUR
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/CONCURConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/CONCURConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/CONCURConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/CONCURConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/CONCURConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if(BUILD_DOCS)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(concur_doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)

