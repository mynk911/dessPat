#include "gtest/gtest.h"

#include "lin.h"

TEST(lin, devTty)
{
    ASSERT_EQ(113, dev_tty());
}
