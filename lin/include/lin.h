#ifndef LIN_LIN_H_
#define LIN_LIN_H_

#include "lin_export.h"

#ifdef __cplusplus
extern "C" {
#endif

int LIN_EXPORT dev_tty();
int LIN_EXPORT pass_word();
int LIN_EXPORT kbhit_example();
int LIN_EXPORT curses_basic();
int LIN_EXPORT curses_charAttr ();

#ifdef __cplusplus
}
#endif

#endif
