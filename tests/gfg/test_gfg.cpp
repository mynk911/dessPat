#include "gtest/gtest.h"
#include "gfg.h"

TEST(gfgArraysFunc, maximumsubarray)
{
    int A[] = {1, 2, 3, -1, 4, 5};
    int B[] = {-1,-2,-3,-4};
    EXPECT_EQ(maximum_subarray(A, 6), 14);
    EXPECT_EQ(maximum_subarray(B, 4), -1);
}

TEST(gfgArraysFunc, findmissingnumber)
{
    int A[] = {1, 2, 3, 4, 6};
    int B[] = {1, 3, 4, 5};
    EXPECT_EQ(find_missing_number(A, 5), 5);
    EXPECT_EQ(find_missing_number(B, 4), 2);
}

TEST(gfgArraysFunc, subarrywithgivensum)
{
    int A[] = {1, 2, 3, 7, 5};
    int B[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int res[2];
    subarry_with_given_sum(A, 5, 12 , res, 2);
    EXPECT_EQ(res[0], 2);
    EXPECT_EQ(res[1], 4);
    subarry_with_given_sum(B, 10, 15, res, 2);
    EXPECT_EQ(res[0], 1);
    EXPECT_EQ(res[1], 5);
}

