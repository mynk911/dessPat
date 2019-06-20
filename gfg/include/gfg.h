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

/// \addtogroup Arrays
/// \{

/// finds the maximum sum contiguous subarray.
/// Uses the kadane's algorithm to find maximum sub array in \f$O(n)\f$
/// time using \f$O(1)\f$ auxiliury space.
///
/// \sa https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
///
/// \code
/// int A[] = { 1, 2, 3, -6, 8 };
/// int res;
/// int out = maximum_subarray(A, 5, &res); // res : 8
/// \endcode
///
/// \param [in] A array of integers.
/// \param [in] n size of the integer array.
/// \param [out] res sum of the maximum sum contiguous subarray
///
/// \return 0 for success
int GFG_EXPORT maximum_subarray(int A[], size_t n, int* res);

/// finds missing number in given array of first n+1 natural numbers.
/// Uses XOR property \f$(x \oplus y) \oplus (x \oplus y \oplus z) = z\f$ to
/// find missing number in \f$O(n)\f$ time complexity using \f$O(1)\f$ auxiliury
/// space.
///
/// \code
/// int A[] = { 1,2,3,5,6 };
/// int res;
/// int out = find_missing_number(A, 5, &res); // res : 4
/// \endcode
///
/// \param [in] A array of natural numbers in range(1, n + 1)
///             with one number missing
/// \param [in] n size of array A
/// \param [out] res missing number in array
///
/// \return 0 for success
int GFG_EXPORT find_missing_number(int A[], size_t n, int* res);

/// finds subarray with elements that sum to value s.
/// uses a method similar to sliding-window technique to find subarray with
/// given sum in \f$O(n)\f$ time using \f$O(1)\f$ auxiliury space.
///
/// \sa https://www.geeksforgeeks.org/window-sliding-technique/
///
/// \code
/// int A[] = { 1,2,3,5,6 };
/// int res[2];
/// int out = subarry_with_given_sum(A, 5, 10, res, 2); // res : {2, 4}
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array A
/// \param [in] s sum of the elements of subarray
/// \param [out] res holds start and end position of result sub array
/// \param [in] size of res
///
/// \return 0 for success, else error code
int GFG_EXPORT subarray_with_given_sum(int A[], size_t n, int s, size_t res[],
                                       size_t m);

/// sort an array of 0,1 and 2s.
/// uses Dutch national flag algorithm to sort an array of 0,1 and 2s in
/// \f$O(n)\f$ time using \f$O(1)\f$ auxiliury space.
///
/// \sa https://en.wikipedia.org/wiki/Dutch_national_flag_problem
///
/// \code
/// int A[] = { 0,1,2,1 };
/// int out = sort_012(A, 4); // A : {0,1,1,2}
/// \endcode
///
/// \param [in,out] A input array which is sorted in place.
/// \param [in] n number of elements in A
///
/// \return 0 for success, else error code
int GFG_EXPORT sort_012(int A[], size_t n);

/// \brief inds an array index such that sum of elements on left is equal to
/// sum of elements on right.
/// uses precomputed sum for rhs to find equilibrium point in \f$O(n)\f$ using
/// \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {1, 3, 5, 2, 2};
/// size_t res;
/// int out = equilibrium_point(A, 5, &res); // res : 3
/// \endcode
///
/// \param [in] A array of positive integers
/// \param [in] n size if array A
/// \param [out] res index of equilibrium
///
/// \return 0 if equilibrium point found, -1 if not found.
int GFG_EXPORT equilibrium_point(int A[], size_t n, size_t* res);

/// finds subsequence with largest sum in a given array.
/// uses dynamic programming to find maximum sum increaing subsequence in
/// \f$O(n^2)\f$ time using \f$O(n)\f$ auxiloury space.
///
/// \sa https://en.wikipedia.org/wiki/Longest_increasing_subsequence
///
/// \code
/// int A[] = {1, 101, 2, 3, 100, 4, 5};
/// int res;
/// int out = maximum_sum_increasing_subsequence(A, 7, &res); // res : 106
/// \endcode
///
/// \param [in] A input array of positive numbers
/// \param [in] n size of input array
/// \param [out] res maximum sum
///
/// \return 0 for success
int GFG_EXPORT maximum_sum_increasing_subsequence(int A[], size_t n, int *res);

/// \brief finds all leaders in array such that leader is greater than all
/// elements to it's rhs.
/// uses reverse traversal to find leaders in \f$O(n)\f$ time using \f$O(n)\f$
/// auxiliury space.
///
/// \code
/// int A[] = {16, 17, 4, 3, 5, 2};
/// size_t res;
/// int out = leaders_in_an_array(A, 6, res, &res_size); // res : (17 5 2)
/// \endcode
///
/// \param [in] A input array  of positive numbers
/// \param [in] n size of input array
/// \param [out] res array of leaders \note there can be upto n leaders
/// \param [out] res_size size of res
///
/// \return 0 for success
int GFG_EXPORT leaders_in_an_array(int A[], size_t n, int* res,
                                   size_t* res_size);
/// \brief finds minimum number of platforms needed to serve a given train
/// timetable.
/// uses simple traversal to find min platforms minimum in \f$O(n)\f$ time
/// using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {900,  940, 950,  1100, 1500, 1800};
/// int B[] = {910, 1200, 1120, 1130, 1900, 2000};
/// int res;
/// int out = minimum_platforms(A,B, 6, &res); // res : 3
/// \endcode
///
/// \param [in] A array of arrival times of trains
/// \param [in] B array of departure times of trains
/// \param [in] n size of array
/// \param [out] res minimum number of platforms
///
/// \return 0 for success
int GFG_EXPORT minimum_platforms(int A[],int B[], size_t n, int* res);

/// finds maximums in all subarrays of size k.
/// finds maximum in all subarrays of input array in \f$O(n)\f$ time using \f$O(1)
/// \f$ auxiliury space.
///
/// \code
/// int A[] = {1, 2, 3, 1, 4, 5, 2, 3, 6};
/// int res[9]; size_t res_size;
/// int out = maximums_of_subarray_size_k(A, 9, 3, res, &res_size);
/// // res : (3, 3, 4, 5, 5, 5 ,6)
/// \endcode
///
/// \param [in] A array of positive numbers
/// \param [in] n size of array A
/// \param [in] k size of subarray
/// \param [out] res result array
/// \param [out] res_size size of result array
///
/// \return 0 for success.
int GFG_EXPORT maximums_of_subarray_size_k(int A[], size_t n, size_t k,
                                           int *res, size_t *res_size);

/// reverses array elements in groups of k.
/// uses simple traversal to reverse groups of k elements in \f$O(n)\f$ time
/// using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {1, 2, 3, 4, 5};
/// int out = reverse_array_in_groups(A, 5, 3);
/// // res : (3, 2, 1, 5, 4)
/// \endcode
///
/// \param [in,out] A array of positive integers. Integers are reversed in
/// place.
/// \param [in] n size of array A.
/// \param [in] k size of the group. \f$k < n\f$
///
/// \return 0 for success.
int GFG_EXPORT reverse_array_in_groups(int A[], size_t n, size_t k);

/// find kth smallest element in a given array of natural numbers.
/// uses modified bubble sort to find kth smallest element in \f$O(k*n)\f$ time
/// using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {7, 10, 4, 3, 20, 15};
/// int res;
/// int out = kth_smallest_element(A, 6, 3, &res); // res : 7
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array A
/// \param [in] k index from left in a sorted array A
/// \param [out] res kth smallest element in  A
///
/// \return 0 for success
int GFG_EXPORT kth_smallest_element(int A[], size_t n, size_t k, int* res);

/// find largest amount of water that can be trapped between given buildings
/// traverses array from left and right to find water trapped in \f$O(n)\f$ time
/// using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {7, 4, 0, 9};
/// long long res;
/// int out = trapping_rainwater(A, 4, &res); // res : 10
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array
/// \param [out] res rain water trapped
///
/// \return 0 for success
int GFG_EXPORT trapping_rainwater(int A[], size_t n, long long* res);

/// find if pythogarean triplet exists in input array.
/// tries combinations 0f three elemnts to find if a pythagorean triplet
/// exists in \f$O(n^2)\f$ time using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {3, 2, 4, 6, 5};
/// int out = pythagorean_triplet(A, 5); // out : (0)
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array
///
/// \return 0 for success, -1 for failure
int GFG_EXPORT pythagorean_triplet(int A[], size_t n);

/// \brief fairly distribute chocolate packets such that there is minimum
/// difference in greatest and least number of chocolates in a packet.
/// uses sorting to find minimum difference in elements separated by m elements
/// in \f$O(n^2)\f$ time using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {3, 4, 1, 9, 56, 7, 9, 12};
/// int res;
/// int out = chocolate_distribution(A, 8, 5, &res); // out : (6)
/// \endcode
///
/// \param [in] A array of natural numbers, each element is number of chocolates
/// in a packet.
/// \param [in] n size of array A
/// \param [in] m number of students
/// \param [out] res minimum difference between largest and smallest packet.
///
/// \return 0 for success
int GFG_EXPORT chocolate_distribution(int A[], size_t n, size_t m, int* res);

/// find all pairs of days one should buy and sell stocks to earn max profit.
/// uses local minima and maxima finding approach to solve in in \f$O(n^2)\f$
/// time using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {100, 180, 260, 310, 40, 535, 695};
/// size_t res[4];
/// size_t res;
/// int out = stock_buy_and_sell(A, 7, res, &res_size); // res : ( 0 3 4 6 )
/// \endcode
///
/// \param [in] A size of array A
/// \param [in] n number of elements in A
/// \param [out] resu array of resulting buy,sell pairs. buys in even and
/// sells in odd indexes.
/// \param [out] res_size size of resu
///
/// \return 0 if a buy,sell pair exists and success,
///         -1 if no buy, sell pair found
int GFG_EXPORT stock_buy_and_sell(int A[], size_t n, size_t* res, size_t* res_size);

/// \brief finds first array element such that elements on it's left are smaller
/// and right are greater.
/// uses memorization to solve in \f$O(n)\f$ time using \f$O(n)\f$ auxiliury
/// space.
///
/// \code
/// int A[] = {4, 2, 5, 7};
/// int res;
/// int out = elements_with_left_side_smaller_and_right_side_greater(
///  A, 4, &res); // out : (5)
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array A
/// \param [out] res holds the resulting element
///
/// \return 0 success
///        -1 element not found
int GFG_EXPORT elements_with_left_side_smaller_and_right_side_greater(int A[],
                                                                    size_t n,
                                                                    int* res);

/// \brief rearranges array elements so that odd elements are smaller and even
/// elements are larger than their next element.
/// uses traversal to solve in \f$O(n)\f$ time using \f$O(1)\f$ auxiliury
/// space.
///
/// \code
/// int A[] = {4, 3, 7, 8, 6, 2, 1};
/// int out = convert_array_into_zigzag_fashion(A, 7);
/// // A : (3, 7, 4, 8, 2, 6, 1)
/// \endcode
///
/// \param [in,out] A array of natural numbers
/// \param [in] n size of array A
///
/// \return 0 for success
int GFG_EXPORT convert_array_into_zigzag_fashion(int A[], size_t n);

/// \brief finds the element which appears only once in an array of sorted
/// numbers in which all other elements appear twice.
/// uses array traversal to solve in \f$O(n)\f$ time using \f$O(1)\f$
/// auxiliury space.
///
/// \code
/// int A[] = {1, 1, 2, 2, 3, 3, 4, 50, 50, 65, 65};
/// int res;
/// int out = find_the_element_that_appears_once_in_sorted_array( A, 11, &res);
/// // out : (4)
/// \endcode
///
/// \param [in] A array of sorted integers where all but one elements appear
/// twice.
/// \param [in] n size of array A
/// \param [out] res element which appears once.
///
/// \return 0 for success.
int GFG_EXPORT find_the_element_that_appears_once_in_sorted_array(int A[],
                                                                  size_t n,
                                                                  int* res);

/// finds kth largest element in a stream of numbers.
/// continuously finds kth largest element in a stream of numbers in
/// \f$O(n*\log k)\f$ time using \f$O(k)\f$ auxiliury space.
///
/// \code
/// int A[] = {1, 2, 3, 4, 5, 6};
/// size_t res[6];
/// size_t res;
/// int out = kth_largest_element_in_a_stream(A, 6, 4, res, &res_size);
/// // res : (-1, -1, -1, 1, 2, 3)
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array A
/// \param [in] k ordinality in largest number series of elements in A
/// \param [out] res contains kth largest elements in array A at every
/// insertion
/// \param [out] res_size size of res.
///
/// \return 0 for success
int  GFG_EXPORT kth_largest_element_in_a_stream(int A[], size_t n, size_t k,
                                                 int* res, size_t *res_size);

/// sorts A according to the order of elements in array B.
/// sorts in \f$O(n*\log k)\f$ time using \f$O(2*n)\f$ auxiliury space.
/// numbers in array A which do not appear in array B are appended at
/// the end of result sorted in ascending order.
///
/// \code
/// int A[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
/// int B[] = {2, 1, 8, 3};
/// int res[11];
/// size_t res_size;
/// int out = relative_sorting(A, 11, B, 4, res, &res_size);
/// // res : (2, 2, 1, 1, 8, 8, 3, 5, 6, 7, 9)
/// \endcode
///
/// \param [in] A array of natural numbers
/// \param [in] n size of array A
/// \param [in] B array of natural numbers, defines order for sorting A
/// \param [in] m size of array B, m < n
/// \param [out] res array of elements in array A sorted as per order in A
/// \param [out] res_size size of res
///
/// \return 0 for success.
int GFG_EXPORT relative_sorting(int A[], size_t n, int B[],  size_t m,
                                int* res, size_t* res_size);

/// traverses given matrix in spiral form.
/// traverses matrix in \f$O(n^2)\f$ time using \f$O(1)\f$ auxiliury space.
///
/// \code
/// int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
/// int res[11];
/// size_t res_size;
/// int out = spirally_traversing_a_matrix(A, 11, B, 4, res, &res_size);
/// // res : (1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10)
/// \endcode
///
/// \param [in] A array of natural numbers, representing matrix in row-major
/// order.
/// \param [in] m rows in A
/// \param [in] n column in A
/// \param [out] res
/// \param [out] res_size
///
/// \return 0 for success.
int GFG_EXPORT spirally_traversing_a_matrix(int A[], size_t m, size_t n,
                                            int* res, size_t* res_size);

/// sorts array elements by frequency.
/// sorts by frequency in \f$O(n)\f$ time using \f$O(n)\f$ auxiliury space.
///
/// \code
/// int A[] = {1, 2, 3, 5, 5};
/// int res[5];
/// size_t res_size;
/// int out = sorting_array_elements_by_frequency(A, 5, B, res, &res_size);
/// // res : (5, 5, 1, 2, 3)
/// \endcode
///
/// \param [in] A array of positive integers
/// \param [in] n size of array A
/// \param [out] res elements of A sorted by frequency
/// \param [out] res_size size of res
///
/// \return 0 for success
int GFG_EXPORT sorting_array_elements_by_frequency(int A[], size_t n,
                                                   int* res, size_t* res_size);

struct arr {
    char a[10];
};

/// find largest number that can be formed by given numbers.
/// uses sorting to solve in \f$O(n^2)\f$ time using \f$O(n)\f$ auxiliury
/// space.
///
///
/// \param As [in] array of type struct arr.
/// \param n [in] size of arrat As.
/// \param res [out] largest number possible as a character array.
/// \param res_size [out] size of res.
///
/// \return 0 for success.
int GFG_EXPORT largest_number_formed_by_array(struct arr As[], size_t n,
                                               char *res, size_t *res_size);

/// \}

/// \addtogroup Strings
/// \{

/// reverse period separated words in a string.
/// uses c library function strtok to solve in \f$O(n)\f$ time using
/// \f$O(1)\f$ auxiliury space.
///
/// \param S [in] string with words separated by period.
/// \param res [out] string wih words reversed..
///
/// \return 0 for success.
///
int GFG_EXPORT reverse_words_in_a_given_string(char *S, char *res);

/// /}

#ifdef __cplusplus
}
#endif 
#endif 
