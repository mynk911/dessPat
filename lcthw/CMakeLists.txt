#add lcthw library

add_custom_target(
   extern_lib
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lcthw
   SOURCES lcthw.c
)

install(FILES lcthw.h DESTINATION include)
install(FILES liblcthw.a DESTINATION bin)
