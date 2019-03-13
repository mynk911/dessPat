cmake_minimum_required(VERSION 3.5) 
project(GOF VERSION 1.0 LANGUAGES CXX)

add_library (gof src/maze.cpp
                 src/maze.h
                 src/mazegame.cpp
                 include/mazegame.h
                 src/mazefactory.cpp
                 include/mazefactory.h
                 src/mazebuilder.cpp
                 include/mazebuilder.h
                 src/shape.cpp
                 include/shape.h
                 src/textview.cpp
                 include/textview.h
                 src/textshape.cpp
                 include/textshape.h)

add_library (GOF::gof ALIAS gof)
include(GenerateExportHeader)
generate_export_header(gof)

target_include_directories(gof
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GOF>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    )

target_compile_features(gof
    PUBLIC cxx_override
    )

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/GOF)

install(
    TARGETS
        gof
    EXPORT
        GOFTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(EXPORT GOFTargets
    FILE GOFTargets.cmake
    NAMESPACE GOF::
    DESTINATION ${INSTALL_CONFIGDIR} 
    )

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GOF
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gof_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GOF
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/GOFConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/CMake/GOFConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/GOFConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
   )

install(
   FILES
     ${CMAKE_CURRENT_BINARY_DIR}/GOFConfig.cmake
     ${CMAKE_CURRENT_BINARY_DIR}/GOFConfigVersion.cmake
     DESTINATION ${INSTALL_CONFIGDIR}
     )

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
if(Doxygen_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target(gof_doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif(Doxygen_FOUND)
endif()
