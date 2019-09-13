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

TEST(lin, cursesBasic)
{
    ASSERT_EQ(0, curses_basic());
}

TEST(lin, cursesCharAttr)
{
    ASSERT_EQ(0, curses_char_attr());
}

TEST(lin, cursesKeyboard)
{
    ASSERT_EQ(0, curses_keyboard());
}

TEST(lin, cursesMultipleWindows)
{
    ASSERT_EQ(0, curses_multiple_windows());
}

TEST(lin, cursesSubwindows)
{
    ASSERT_EQ(0, curses_subwindows());
}
