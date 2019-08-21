#include <stdio.h>

#include "win.h"
#include <Windows.h>

int WinHello()
{
    MessageBox (NULL, TEXT ("Hello, Windows 98!"), TEXT ("HelloMsg"), 0);
    return 0 ;
}


int MessageBoxPrintf(TCHAR *szCaption, TCHAR* szFormat, ...)
{
    TCHAR szBuffer[1024];
    va_list pArgList;

    va_start(pArgList, szFormat);
    _vsntprintf(szBuffer, sizeof (szBuffer)/sizeof (TCHAR), szFormat, pArgList);
    va_end(pArgList);

    return MessageBox(NULL, szBuffer, szCaption, 0);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int drawWindow()
{
    static TCHAR szAppName[] = TEXT("HelloWin");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if(!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires windows NT"), szAppName,
                   MB_ICONERROR);
        return -1;
    }
    hwnd = CreateWindow(szAppName,
                        TEXT("The Hello Program"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        GetModuleHandle(NULL),
                        NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch(message)
    {
    case WM_CREATE:
        PlaySound(TEXT("helloWin.wav"), NULL, SND_FILENAME | SND_ASYNC);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("Hello windows 98!!"), -1, &rect, DT_SINGLELINE |
                 DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
