#include <Windows.h>

#include "win.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
PSTR szCmdLine, int iCmdShow)
{
    WinHello();
    int cxScreen, cyScreen;
    cxScreen = GetSystemMetrics(SM_CXSCREEN);
    cyScreen = GetSystemMetrics(SM_CYSCREEN);
    MessageBoxPrintf(TEXT("ScreenSize"),
                     TEXT("The Screen is %i pixels wide by %i pixels high"),
                     cxScreen, cyScreen);
    return 0 ;
}
