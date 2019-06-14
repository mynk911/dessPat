#include <iostream>
#include <thread>

#include "win.h"
#include <windows.h>

int test()
{
    MessageBox (NULL, TEXT ("Hello, Windows 98!"), TEXT ("HelloMsg"), 0) ;
    return 0 ;
}


