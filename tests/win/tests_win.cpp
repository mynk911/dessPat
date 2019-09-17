#include "gtest/gtest.h"
#include "win.h"

TEST(win, wintest){
    int a = WinHello();
    EXPECT_EQ(a, 0);
}

TEST(win, MessageBoxPrintf){
#ifdef _UNICODE
    int a = MessageBoxPrintf(L"FormattedPrintTest", L"this is number Five:%d", 5);
#else
    int a = MessageBoxPrintf("FormattedPrintTest", "this is number Five:%d", 5);
#endif
    EXPECT_EQ(a, 1);
}

TEST(win, drawWindow){
    int a = drawWindow();
    EXPECT_EQ(a, 0);
}

TEST(win, sysMetrics)
{
    EXPECT_EQ(sysmets(), 0);
}


