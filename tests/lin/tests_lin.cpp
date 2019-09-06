#include "gtest/gtest.h"

#include "lin.h"

TEST(lin, devTty)
{
    ASSERT_EQ(113, dev_tty());
}

TEST(lin, passWord)
{
    ASSERT_EQ(0, pass_word());
}

TEST(lin, kbhitExample)
{
    ASSERT_EQ(0, kbhit_example());
}

TEST(lin, simpleCurses)
{
    ASSERT_EQ(0, simple_curses());
}

TEST(lin, simpleCurses2)
{
    ASSERT_EQ(0, simple_curses2());
}
