#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gfg.h"

using ::testing::ElementsAre;
using ::testing::_;
TEST(gfgArraysFunc, maximumSubarray)
{
    int A[] = {1, 2, 3, -1, 4, 5};
    int res;
    int a = maximum_subarray(A, 6, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 14);
}

TEST(gfgArraysFunc, findMissingNumber)
{
    int A[] = {1, 2, 3, 4, 6};
    int res;
    int a = find_missing_number(A, 5, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 5);
}

TEST(gfgArraysFunc, subarrayWithGivenSum)
{
    int A[] = {1, 2, 3, 7, 5};
    size_t res[2];
    int a = subarray_with_given_sum(A, 5, 12 , res, 2);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(2, 4));
}

TEST(gfgArraysFunc, sort012)
{
    int A[] = {0, 2, 1, 2, 0};
    int a = sort_012(A, 5);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(A, ElementsAre(0,0,1,2,2));
}

TEST(gfgArraysFunc, equilibriumPoint)
{
    int A[] = {1, 3, 5, 2, 2};
    size_t res;
    int a = equilibrium_point(A, 5, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 3);
}

TEST(gfgArraysFunc, maximumSumincreasIngSubsequence)
{
    int A[] = {1, 101, 2, 3, 100, 4, 5};
    int res;
    int a = maximum_sum_increasing_subsequence(A, 7, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 106);
}

TEST(gfgArraysFunc, leadersInAnArray)
{
    int A[] = {16, 17, 4, 3, 5, 2};
    int res[6];
    size_t res_size;
    int a = leaders_in_an_array(A, 6, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(17, 5, 2, _, _, _));
}

TEST(gfgArraysFunc, minimumPlatforms)
{
    int A[] = {900,  940, 950,  1100, 1500, 1800};
    int B[] = {910, 1200, 1120, 1130, 1900, 2000};
    int res;
    int a = minimum_platforms(A, B, 6, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 3);
}

TEST(gfgArraysFunc, maximumsOfSubarraySizeK)
{
    int A[] = {1, 2, 3, 1, 4, 5, 2, 3, 6};
    int res[7];
    size_t res_size;
    int a = maximums_of_subarray_size_k(A, 9, 3, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(3, 3, 4, 5, 5, 5 ,6));
}

TEST(gfgArraysFunc, reverseArrayInGroups)
{
    int A[] = {1, 2, 3, 4, 5};
    int a = reverse_array_in_groups(A, 5, 3);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(A, ElementsAre(3, 2, 1, 5, 4));
}

TEST(gfgArraysFunc, kthSmallestElement)
{
    int A[] = {7, 10, 4, 3, 20, 15};
    int res;
    int a = kth_smallest_element(A, 6, 3, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 7);
}

TEST(gfgArraysFunc, trappingRainwater)
{
    int A[] = {7, 4, 0, 9};
    long long res;
    int a = trapping_rainwater(A, 4, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 10);
}

TEST(gfgArraysFunc, pythagoreanTriplet)
{
    int A[] = {3, 2, 4, 6, 5};
    int a = pythagorean_triplet(A, 5);
    EXPECT_EQ(a, 0);
}

TEST(gfgArraysFunc, chocolateDistribution)
{
    int A[] = {3, 4, 1, 9, 56, 7, 9, 12};
    int res;
    int a = chocolate_distribution(A, 8, 5, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 6);
}

TEST(gfgArraysFunc, stockBuyAndSell)
{
    int A[] = {100, 180, 260, 310, 40, 535, 695};
    size_t res[4];
    size_t res_size;
    int a = stock_buy_and_sell(A, 7, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(0, 3, 4, 6));
}

TEST(gfgArraysFunc, elementsWithLeftSideSmallerAndRightSideGreater)
{
    int A[] = {4, 2, 5, 7};
    int res;
    int a = elements_with_left_side_smaller_and_right_side_greater(A, 4, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 5);
}

TEST(gfgArraysFunc, convertArrayIntoZigzagFashion)
{
    int A[] = {4, 3, 7, 8, 6, 2, 1};
    int a = convert_array_into_zigzag_fashion(A, 7);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(A, ElementsAre(3, 7, 4, 8, 2, 6, 1));
}

TEST(gfgArraysFunc, findTheElementThatAppearsOnceInSortedArray)
{
    int A[] = {1, 1, 2, 2, 3, 3, 4, 50, 50, 65, 65};
    int res;
    int a = find_the_element_that_appears_once_in_sorted_array(A, 11, &res);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(res, 4);
}

TEST(gfgArraysFunc, kthLargestElementInAStream)
{
    int A[] = {1, 2, 3, 4, 5, 6};
    int res[6];
    size_t res_size;
    int a = kth_largest_element_in_a_stream(A, 6, 4, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(-1, -1, -1, 1, 2, 3));
}

TEST(gfgArraysFunc, relativeSorting)
{
    int A[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    int B[] = {2, 1, 8, 3};
    int res[11];
    size_t res_size;
    int a = relative_sorting(A, 11, B, 4, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(2, 2, 1, 1, 8, 8, 3, 5, 6, 7, 9));
}

TEST(gfgArraysFunc, spirallyTraversingAMatrix)
{
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int res[16];
    size_t res_size;
    int a = spirally_traversing_a_matrix(A, 4, 4, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9,
                                 5, 6, 7, 11, 10));
}

TEST(gfgArraysFunc, sortingArrayElementsByFrequency)
{
    int A[] = {19, 14, 15, 8, 1, 3, 6, 12, 5, 7, 17, 3, 6, 8, 2, 8, 18, 10, 15,
               7, 8, 20, 8, 13, 18, 9, 2, 1, 1, 10, 11, 8, 14, 20, 14, 1, 2,
               15, 13, 21, 6, 7, 11, 1, 8, 9, 18, 19, 18, 4, 4, 19, 9, 12, 17,
               13, 21, 14, 13, 12, 4, 13, 1, 12, 18, 21, 15, 5, 4, 13, 7, 3, 3,
               18, 19, 4, 21, 17, 11, 3, 15, 7, 5, 13, 14, 17, 19, 21, 2, 8,
               13, 20, 11, 11, 2, 2, 13, 16, 2, 7, 3, 21, 10, 9, 13, 11, 9, 12,
               5};
    int res[109];
    size_t res_size;
    int a = sorting_array_elements_by_frequency(A, 109, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_THAT(res, ElementsAre(13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                                 8, 8, 8, 8, 8, 8, 8, 8,
                                 2, 2, 2, 2, 2, 2, 2,
                                 1, 1, 1, 1, 1, 1,
                                 3, 3, 3, 3, 3, 3,
                                 7, 7, 7, 7, 7, 7,
                                 11, 11, 11, 11, 11, 11,
                                 18, 18, 18, 18, 18, 18,
                                 21, 21, 21, 21, 21, 21,
                                 4, 4, 4, 4, 4,
                                 9, 9, 9, 9, 9,
                                 12, 12, 12, 12, 12,
                                 14, 14, 14, 14, 14,
                                 15, 15, 15, 15, 15,
                                 19, 19, 19, 19, 19,
                                 5, 5, 5, 5,
                                 17, 17, 17, 17,
                                 6, 6, 6,
                                 10, 10, 10,
                                 20, 20, 20,
                                 16));
}

TEST(gfgArraysFunc, largestNumberFormedByArray)
{
    struct arr A[] = {{"3"}, {"30"}, {"34"}, {"5"}, {"9"}};
    char res[10];
    size_t res_size;
    int a = largest_number_formed_by_array(A, 5, res, &res_size);
    EXPECT_EQ(a, 0);
    EXPECT_STREQ(res, "9534330");
}
