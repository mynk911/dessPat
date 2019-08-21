cmake_minimum_required(VERSION 3.12)
project(WIN VERSION 0.1 LANGUAGES C)

add_library(win src/win.c include/win.h)
add_library(WIN::win ALIAS win)

if(UNICODE)
    set(_UNICODE "ON")
endif()

#configure a header file to pass some of the cmake settings to the source code
configure_file (
                 "${CMAKE_CURRENT_SOURCE_DIR}/winConfig.h.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/winConfig.h"
               )

include(GenerateExportHeader)
generate_export_header(win)
target_include_directories(win
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/WIN>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

find_library(LIBWMM winmm)
target_link_libraries(win ${LIBWMM})

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/WIN)

install(
    TARGETS
        win
    EXPORT
        WINTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT WINTargets
    FILE WINTargets.cmake
    NAMESPACE WIN::
    DESTINATION ${INSTALL_CONFIGDIR}
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/WIN
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/win_export.h
              ${CMAKE_CURRENT_BINARY_DIR}/winConfig.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/WIN
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/WINConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/WINConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/WINConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/WINConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/WINConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(win_doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif(DOXYGEN_FOUND)
endif()

add_executable(wintest WIN32 src/win_test.c src/win.c)
                    
target_include_directories(wintest
                        PUBLIC
                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
                        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                        PRIVATE
                        ${CMAKE_CURRENT_SOURCE_DIR}/src
                        )
target_link_libraries(wintest ${LIBWMM})
option(UNICODE "use UNICODE" OFF)
