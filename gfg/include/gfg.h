/**
  \file gfg.h

  \brief this file contains interfaces to functions solvingproblems I am working
  on.

  I am putting together this file to keep track of problems I have solved as
  well as a reference when I need a quick brush up of common topics. In this
  file I try to explain the purpose and usage of each function.

  \author mayank bansal
  */

#ifndef GFG_GFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gfg_export.h"
/**
  \brief find the maximum sum contiguous subarray.

  find the maximum sum contiguous subarray in a given array with a
  O(n) time complexity and with O(1) auxiliury space.

  Usage : 

  \code
  int array[] = {1, 2, 3, -6, 8};
  int res = maximum_subarray(array, 5);
  printf("res : %d", res); // res : 8
  \endcode
 
  \param A array of integers.
  \param n size of the integer array.
  \return sum of the maximum sum contiguous subarray

*/
int GFG_EXPORT maximum_subarray(int A[], int n);

/*!
 * \brief find missing number in given array of natural numbers.
 *
 * O(n) time complexity with O(1) auxiliury space.
 *
 * \code
 * int array[] = {1,2,3,5,6};
 * int res = find_missing_number(array, 5);
 * printf("res : %d", res); // res : 4)
 * \endcode
 *
 * \param A array of integers in range (1,n+1) with one number missing
 * \param n size of array A
 * \return missing number in array
 */
int GFG_EXPORT find_missing_number(int A[], int n);
void GFG_EXPORT subarry_with_given_sum(int A[], int n, int s);
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
#ifdef __cplusplus
}
#endif 
#endif 
