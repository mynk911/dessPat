#include <sstream>

#include "cs180.h"
#include "gtest/gtest.h"

TEST(cs180, stableMatching)
{
    std::stringstream in, out;

    in << "2 m1 m2 w1 w2 m1 w2 w1 m2 w1 w2 w1 m1 m2 w2 m1 m2\0";
    std::string s("w1 m2\n"
		  "w2 m1\n");
    auto i = cs180::stable_matching(in, out);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(s, out.str());
}
