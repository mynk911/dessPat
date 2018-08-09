#add the main library
add_library (gfg gfg.c)

install (TARGETS gfg DESTINATION bin)
install (FILES gfg.h DESTINATION include)