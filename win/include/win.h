#ifndef WIN_H_
#define WIN_H_

#include "winConfig.h"
#include <tchar.h>
#include <Windows.h>

#include "win_export.h"

#ifdef __cplusplus
extern "C" {
#endif

int WIN_EXPORT WinHello();
int WIN_EXPORT MessageBoxPrintf(TCHAR *szCaption, TCHAR* szFormat, ...);
int WIN_EXPORT drawWindow();
int WIN_EXPORT sysmets();
#ifdef __cplusplus
}
#endif

#endif // WIN_H_
