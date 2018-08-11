#add lcthw library
add_library(lcthw lcthw.c)

install (TARGETS lcthw DESTINATION bin)
install (FILES lcthw.h DESTINATION include)
