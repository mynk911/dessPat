#add lcthw library

add_custom_target(
   extern_lib
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lcthw
   SOURCES ex1.c ex3.c Makefile
)

install(FILES lcthw.h DESTINATION include)
install(FILES liblcthw.a DESTINATION bin)
