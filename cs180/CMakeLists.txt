#add library cs180
add_library(cs180 cs180.cpp)

#install library
install(TARGETS cs180 DESTINATION bin)
install(FILES cs180.h DESTINATION include)
