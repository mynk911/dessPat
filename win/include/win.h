#ifndef WIN_H_
#define WIN_H_

#include "winConfig.h"
#include <tchar.h>

#include "win_export.h"

#ifdef __cplusplus
extern "C" {
#endif

int WIN_EXPORT WinHello();
int WIN_EXPORT MessageBoxPrintf(TCHAR *szCaption, TCHAR* szFormat, ...);
int WIN_EXPORT drawWindow();
#ifdef __cplusplus
}
#endif

#endif // WIN_H_
