#include "gtest/gtest.h"
#include "gfg.h"

TEST(maximum_subarray, checkForEquality)
{
    int A[] = {1, 2, 3, -1, 4, 5};
    int B[] = {-1,-2,-3,-4};
    EXPECT_EQ(maximum_subarray(A, 6), 14);
    EXPECT_EQ(maximum_subarray(B, 4), -1);
}
