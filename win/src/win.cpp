#include <iostream>
#include <thread>

#include "win.h"
#include <windows.h>

int win_hello()
{
    MessageBox (NULL, TEXT ("Hello, Windows 98!"), TEXT ("HelloMsg"), 0) ;
    return 0 ;
}


