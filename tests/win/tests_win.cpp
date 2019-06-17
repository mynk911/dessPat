#include "gtest/gtest.h"
#include "win.h"

TEST(win, wintest){
    int a = win_hello();
    EXPECT_EQ(a, 0);
}
