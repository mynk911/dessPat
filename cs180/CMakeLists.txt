#add library cs180
add_library(cs180 cs180.cpp)
target_include_directories(cs180
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
    ${PROJECT_SOURCE_DIR}/cs180
    )

#install library
install(TARGETS cs180 DESTINATION bin)
