/**
  \file gfg.h

  \brief this file contains interfaces to functions solving problems I am working
  on.

  I am putting together this file to keep track of problems I have solved as
  well as a reference when I need a quick brush up of common topics. In this
  file I try to explain the purpose of each function.

  \author mayank bansal
 */

#ifndef GFG_GFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "gfg_export.h"

/*!
 * \brief finds the maximum sum contiguous subarray.
 */
int GFG_EXPORT maximum_subarray(int A[], size_t n, int* res);

/*!
 * \brief finds missing number in given array of first n+1 natural numbers.
 */
int GFG_EXPORT find_missing_number(int A[], size_t n, int* res);

/*!
 * \brief finds subarray with elements that sum to value s.
 */
int GFG_EXPORT subarray_with_given_sum(int A[], size_t n, int s, size_t res[],
                                       size_t m);

/*!
 * \brief sort an array of 0,1 and 2s.
 */
int GFG_EXPORT sort_012(int A[], size_t n);

/*!
 * \brief finds an array index such that sum of elements on left is equal to
 * sum of elements on right.
 */
int GFG_EXPORT equilibrium_point(int A[], size_t n, size_t* res);

/*!
 * \brief finds subsequence with largest sum in a given array.
 */
int GFG_EXPORT maximum_sum_increasing_subsequence(int A[], size_t n, int *res);


/*!
 * \brief finds all leaders in array such that leader is greater than all
 * elements to it's rhs.
 */
int GFG_EXPORT leaders_in_an_array(int A[], size_t n, int* res,
                                   size_t* res_size);

/*!
 * \brief finds minimum number of platforms needed to serve a given train
 * timetable.
 */
int GFG_EXPORT minimum_platforms(int A[],int B[], size_t n, int* res);

/*!
 * \brief finds maximums in all subarrays of size k.
 */
int GFG_EXPORT maximums_of_subarray_size_k(int A[], size_t n, size_t k,
                                           int *res, size_t *res_size);

/*!
 * \brief reverses array elements in groups of k.
 */
int GFG_EXPORT reverse_array_in_groups(int A[], size_t n, size_t k);

/*!
 * \brief find kth smallest element in a given array of natural numbers.
 */
int GFG_EXPORT kth_smallest_element(int A[], size_t n, size_t k, int* res);

/*!
 * \brief find largest amount of water that can be trapped between given
 * buildings
 */
int GFG_EXPORT trapping_rainwater(int A[], size_t n, long long* res);

/*!
 * \brief find if pythogarean triplet exists in input array
 */
int GFG_EXPORT pythagorean_triplet(int A[], size_t n);

/*!
 * \brief fairly distribute chocolate packets such that there is minimum
 * difference in greatest and least number of chocolates in a packet.
 */
int GFG_EXPORT chocolate_distribution(int A[], size_t n, size_t m, int* res);

/*!
 * \brief find all pairs of days one should buy and sell stocks to earn max
 * profit.
 */
int GFG_EXPORT stock_buy_and_sell(int A[], size_t n, size_t* res, size_t* res_size);

/*!
 * \brief finds first array element such that elements on it's left are smaller
 * and right are greater.
 */
int GFG_EXPORT elements_with_left_side_smaller_and_right_side_greater(int A[],
                                                                    size_t n,
                                                                    int* res);

/*!
 * \brief rearranges array elements so that odd elements are smaller and even
 * elements are larger than their next element.
 */
int GFG_EXPORT convert_array_into_zigzag_fashion(int A[], size_t n);

/*!
 * \brief finds the element which appears only once in an array of sorted
 * numbers in which all other elements appear twice.
 */
int GFG_EXPORT find_the_element_that_appears_once_in_sorted_array(int A[],
                                                                  size_t n,
                                                                  int* res);

/*!
 * \brief finds kth largest element in a stream of numbers.
 */
int  GFG_EXPORT kth_largest_element_in_a_stream(int A[], size_t n, size_t k,
                                                 int* res, size_t *res_size);

/*!
 * \brief sorts A according to the order of elements in array B.
 */
int GFG_EXPORT relative_sorting(int A[], size_t n, int B[],  size_t m,
                                int* res, size_t* res_size);

/*!
 * \brief traverses given matrix in spiral form.
 */
int GFG_EXPORT spirally_traversing_a_matrix(int A[], size_t m, size_t n,
                                            int* res, size_t* res_size);
/*!
 * \brief sorts array elements by frequency.
 */
int GFG_EXPORT sorting_array_elements_by_frequency(int A[], size_t n,
                                                   int* res, size_t* res_size);

struct arr {
    char a[10];
};

/*!
 * \brief find largest number that can be formed by given numbers.
 */
int GFG_EXPORT largest_number_formed_by_array(struct arr As[], size_t n,
                                               char *res, size_t *res_size);

/*!
 * \brief reverse period separated words in a string.
 */
int GFG_EXPORT reverse_words_in_a_given_string(char *S, char *res);

#ifdef __cplusplus
}
#endif 
#endif 
