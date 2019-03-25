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
int GFG_EXPORT maximum_subarray(int A[], int n);

/*!
 * \brief finds missing number in given array of first n+1 natural numbers.
 */
int GFG_EXPORT find_missing_number(int A[], int n);

/*!
 * \brief finds subarray with elements that sum to value s.
 */
int GFG_EXPORT subarry_with_given_sum(int A[], int n, int s, int res[], size_t m);
void GFG_EXPORT sort_012(int A[], int n);
void GFG_EXPORT equilibrium_point(int A[], int n);
void GFG_EXPORT maximum_sum_increasing_subsequence(int A[], int n);
void GFG_EXPORT leaders_in_an_array(int A[], int n);
void GFG_EXPORT minimum_platforms(int A[],int B[], int n);
void GFG_EXPORT maximums_of_subarray_size_k(int A[], int n, int k);
void GFG_EXPORT reverse_array_in_groups(int A[], int n, int k);
void GFG_EXPORT kth_smallest_element(int A[], int n, int k);
void GFG_EXPORT trapping_rainwater(int A[], int n);
void GFG_EXPORT pythagorean_triplet(int A[], int n);
void GFG_EXPORT chocolate_distribution(int A[], int n, int m);
void GFG_EXPORT stock_buy_and_sell(int A[], int n);
void GFG_EXPORT elements_with_left_side_smaller_and_right_side_greater(int A[], int n);
void GFG_EXPORT convert_array_into_zigzag_fashion(int A[], int argc);
void GFG_EXPORT find_the_element_that_appears_once_in_sorted_array(int A[], int n);
void  GFG_EXPORT kth_largest_element_in_a_stream(int A[], int n, int k);
void GFG_EXPORT relative_sorting(int A[], int B[], int n, int m);
void GFG_EXPORT spirally_traversing_a_matrix(int A[], int m, int n);
void GFG_EXPORT sorting_array_elements_by_frequency(int A[], int n);

struct arr {
    char a[10];
};

int GFG_EXPORT largest_number_formed_by_array(struct arr As[], int n);
#ifdef __cplusplus
}
#endif 
#endif 
