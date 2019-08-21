#include <sstream>
#include "gtest/gtest.h"
#include "concur.h"


TEST(concurtests, exec)
{
   std::stringstream s;
   exec(s);
   EXPECT_STREQ(s.str().c_str(), "Hello concur World!");
}

TEST(concurtests, oops)
{
    EXPECT_EQ(oops(), 0);
}

TEST(concurtests, WaitForFinish)
{
    EXPECT_EQ(WaitForFinish(), 0);
}

TEST(concurtests, WaitForFinishRAII)
{
    EXPECT_EQ(WaitForFinishRAII(), 0);
}
