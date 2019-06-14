#include "gtest/gtest.h"
#include "win.h"

TEST(win, wintest){
    int a = test();
    EXPECT_EQ(a, 0);
}
