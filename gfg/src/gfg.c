/// \file gfg.c
/// \brief this file contains implementations to some coding problems I am
/// working on.
///
/// I am putting together this file to keep track of problems I have solved as
/// well as a reference when I need a quick brush up of common topics. In this
/// file I include the underlying algorithms used to solve problems as well as
/// relevent references.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "gfg.h"
#include "string.h"

#include "dbg.h"

/** \defgroup Arrays Array problems
 *  \brief Basic problems which act upon array input 
 */

static int loc[1010];
static int aux[1010];
static size_t aux_index[1010];

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int rev_cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}
int cus_cmp(const void* a, const void* b)
{
    const int x = *((const int *)a);
    const int y = *((const int *)b);
    if (aux[x] == aux[y])
        return x - y;
    else
        return aux[y] - aux[x];
}

void swap(int A[], size_t a, size_t b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

/// \addtogroup Arrays
/// \{

///
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
///
int maximum_subarray(int A[], size_t n, int* res)
{
    int maxSoFar = INT_MIN, maxAtIndex = 0, temp = 0;
    for (size_t index = 0; index<n; index++)
    {
        //get max for subarray that ends at index
        temp = maxAtIndex + A[index];
        maxAtIndex = temp < A[index] ? A[index] : temp;

        //update global max
        if (maxSoFar < maxAtIndex) {
            maxSoFar = maxAtIndex;
        }
    }

    *res = maxSoFar;
    return 0;
}

///
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
/// \param [in] A array of natural numbers in range(1, n + 1) with one number missing
/// \param [in] n size of array A
/// \param [out] res missing number in array
///
/// \return 0 for success
///
int find_missing_number(int A[], size_t n, int* res)
{
    // Calculate X = XOR of first n+1 natural numbers
    int X = 0;
    for(size_t i = 1; i <= n+1; i++)
        X ^= i;

    // Calculate Y = XOR of all numbers in array
    int Y = 0;
    for(size_t i = 0;i < n; i++)
        Y ^= A[i];

    // return X^Y = missing number
    *res = X^Y;
    return 0;
}

///
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
///
int subarray_with_given_sum(int A[], size_t n, int s, size_t res[], size_t m)
{
    size_t start = 0, end = 0;
    int curr = 0;

    // loop invariant : curr is sum of elements in [start,end)
    while(start<n)
    {
        if(curr == s) break;
        else if(curr < s)
        {
            if(end < n)
                curr += A[end++];
            else break;
        }
        else curr -= A[start++];
    }

    // put results in res if curr == s
    if(curr == s)
    {
        check(m >= 2, "result array should be atleast 2 integer length");
        res[0] = start+1;
        res[1] = end;
        return 0;
    }
    else return -1;
error:
    return -1;
}

///
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
///
int sort_012(int A[], size_t n)
{
    size_t b = 0, m = 0, e = n;
    // loop invariant : 0s in [0,b), 1s in [b,m),
    // [m,e) is unsorted & 2s in [e,n)
    while (m < e)
    {
        if (A[m] == 0)
        {
            if (b != m) swap(A, b, m);
            b++; m++;
        }
        else if (A[m] == 1)
        {
            m++;
        }
        else if (A[m] == 2)
        {
            e--;
            swap(A, m, e);
        }
    }
    return 0;
}

///
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
///
int equilibrium_point(int A[], size_t n, size_t *res)
{
    //
    if (n == 1)
        *res = 1;

    // find sum of all array elements
    int sum = 0;
    for (size_t i = 0; i < n; i++)
        sum += A[i];

    // loop invariant : sl = sum of elements in [0, i)
    // sr = sum of elements in (i,n)
    size_t i = 0;
    int sl = 0, sr = sum - A[0];
    for (i = 1; i < n; i++)
    {
        sl += A[i - 1];
        sr -= A[i];
        if (sl == sr)
        {
            *res = i + 1;
            break;
        }
    }

    if (i == n && n != 1) return -1;
    return 0;
}

///
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
///
int maximum_sum_increasing_subsequence(int A[], size_t n, int* res)
{
    // find MIS ending at index i
    // loop invariant : aux[i] = sum of MIS starting in [0,i] and ending at i
    for (size_t i = 0; i < n; i++)
    {
        aux[i] = A[i];
        //loop invariant : aux[i] = sum of MIS for subarray [0,j] and ending at i
        for (size_t j = 0; j < i; j++)
        {
            if (A[j] < A[i] && aux[i] < aux[j] + A[i])
            {
                aux[i] = aux[j] + A[i];
            }
        }
    }

    // find largest MIS ending at any index.
    int max_sum = aux[0];
    for (size_t i = 1; i < n; i++)
    {
        if (aux[i] > max_sum)
        {
            max_sum = aux[i];
        }
    }

    *res = max_sum;
    return 0;
}

///
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
///
int leaders_in_an_array(int A[], size_t n, int *res, size_t* res_size)
{
    //loop invariant : A[aux_index[i]] is the largest element in [j,n)
    size_t i = 0;
    aux_index[i] = n - 1;
    for (size_t j = n - 2; j < (size_t)-1; j--)
    {
        if (A[j] >= A[aux_index[i]])
        {
            i++;
            aux_index[i] = j;
        }
    }

    // copy leaders to result in reverse order
    *res_size = 0;
    while (i < (size_t)-1)
    {
        res[*res_size] = A[aux_index[i]];
        (*res_size)++;
        i--;
    }

    return 0;
}

///
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
///
int minimum_platforms(int A[], int B[], size_t n, int* res)
{
    // sort arrival and departure of trains in ascending order.
    qsort(A, n, sizeof(int), cmp);
    qsort(B, n, sizeof(int), cmp);

    // count = number of platforms
    int count = 0;
    *res = 1;
    size_t i = 0, j = 0;
    while (i < n && j < n)
    {
        if (A[i] < B[j])
        {
            count++; i++;
            if (count > *res) *res = count;
        }
        else
        {
            count--; j++;
        }
    }
    return 0;
}


///
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
///
int maximums_of_subarray_size_k(int A[], size_t n, size_t k, int* res,
                                size_t *res_size)
{
    size_t  maxpos = UINT_MAX;
    *res_size = 0u;

    // loop invariant : maxpos is the index of largest value in range (i, j)
    for (size_t i = 0, j = k - 1; j < n; j++, i++)
    {
        if (maxpos < i || maxpos == UINT_MAX)
        {
            maxpos = i;
            for (size_t l = i + 1; l <= j; l++)
                if (A[l] > A[maxpos]) maxpos = l;
        }
        else
        {
            if (A[j] > A[maxpos])
                maxpos = j;
        }

        res[(*res_size)++] = A[maxpos];
    }

    return 0;
}

///
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
///
int reverse_array_in_groups(int A[], size_t n, size_t k)
{
    for (size_t i = 0; i < n; i += k)
    {
        // loop invariant : range i..l r..(i+k-1) is reversed
        size_t l = i, r = (i + k - 1 < n) ? i + k - 1 : n - 1;
        while (l < r)
        {
            int temp;
            temp = A[l];
            A[l] = A[r];
            A[r] = temp;
            l++; r--;
        }
    }

    return 0;
}

///
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
///
int kth_smallest_element(int A[], size_t n, size_t k, int* res)
{
    // loop invariant : [n-1-i,n) contains ith smallest to smallest
    // elements in sorted in reverse order
    for (size_t i = 0; i < k; i++)
    {
        // loop invariant : A[j+1] is smallest element in range (0, j+1)
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (A[j] < A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }

    *res = A[n - k];
    return 0;
}

///
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
///
int trapping_rainwater(int A[], size_t n, long long* res)
{
    size_t l = 0, r = n - 1;
    int maxl = 0, maxr = 0;
    long long water = 0;

    // loop invariant : water = amountof rain water trapped in ranges
    // (0, l) and (r, n)
    while (l < r)
    {
        if (A[l] < A[r])
        {
            if (maxl < A[l]) maxl = A[l];
            else water += maxl - A[l];
            l++;
        }
        else
        {
            if (maxr < A[r]) maxr = A[r];
            else water += maxr - A[r];
            r--;
        }
    }
    *res = water;
    return 0;
}

///
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
///
int pythagorean_triplet(int A[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        A[i] *= A[i];
    }
    // reverse sort
    qsort(A, n, sizeof(int), rev_cmp);
    int flag = 0;
    for (size_t i = 0; i < n - 2; i++)
    {
        size_t l = i + 1, r = n - 1;
        while (l < r)
        {
            if (A[l] + A[r] == A[i])
            {
                flag = 1;
                break;
            }
            else (A[l] + A[r] < A[i]) ? r-- : l++;
        }
        if (flag == 1) break;
    }
    if (flag != 1) return -1;
    return 0;
}



///
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
///
int chocolate_distribution(int A[], size_t n, size_t m, int* res)
{
    qsort(A, n, sizeof(int), cmp);

    size_t l = 0, r = m - 1;
    *res = INT_MAX;

    // mindiff == smallest difference between A[l], A[l+m-1] in range (0,r)
    while (r < n)
    {
        if (A[r] - A[l] < *res)
            *res = A[r] - A[l];
        l++; r++;
    }

    return 0;
}



struct iv {
    size_t buy;
    size_t sell;
};

///
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
///
int stock_buy_and_sell(int A[], size_t n, size_t* resu, size_t* res_size)
{
    struct iv res[505];

    // loop invariant : count = number of local minima followed by local maxima
    size_t count = 0, i = 0;
    while (i < n) {
        // loop invariant : range A(i',i) consists of non-increasing integers
        while (i < n - 1 && A[i + 1] <= A[i]) i++;

        if (i == n - 1) break;
        res[count].buy = i++;

        // loop invariant : range (i', i-1) consistsof non-decreasing integers
        while (i < n && A[i] >= A[i - 1]) i++;

        res[count].sell = i - 1;
        count++;
    }

    if (count == 0) return -1;
    else {
        *res_size = 0;
        for (size_t i = 0; i < count; i++)
        {
            resu[*res_size] = res[i].buy;
            resu[*res_size+1] = res[i].sell;
            *res_size += 2;
        }
    }
    return 0;
}



///
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
///
int elements_with_left_side_smaller_and_right_side_greater(int A[], size_t n,
                                                           int* res)
{
    int min_right = INT_MAX;

    // loop invariant : min_right is smallest element in range A[i, n)
    for (size_t i = n - 1; i < UINT_MAX; i--)
    {
        if (A[i] < min_right)
            min_right = A[i];
        aux[i] = min_right;
    }

    // loop invariant : *res is largest in range A(0, i]
    size_t i; *res = 0;
    for (i = 0; i < n; i++)
    {
        if (A[i] > *res)
            *res = A[i];
        if (i != 0 && i != n - 1 && *res == A[i] && A[i] == aux[i])
        {
            break;
        }
    }

    if (i == n) return -1;
    return 0;
}

///
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
///
int convert_array_into_zigzag_fashion(int A[], size_t n)
{
    int flag = 0; int temp;

    // loop invariant : In range A(0, i) A[odd] < A[even]
    for (size_t i = 0; i < n - 1; i++)
    {
        if (flag == 0)
        {
            if (A[i] > A[i + 1])
            {
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
        else if (flag == 1)
        {
            if (A[i] < A[i + 1])
            {
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
        flag = (flag == 0) ? 1 : 0;
    }

    return 0;
}

///
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
///
int find_the_element_that_appears_once_in_sorted_array(int A[], size_t n,
                                                                int* res)
{
    size_t i;

    // loop invariant : range A[0,i-1] has property A[k] == A[k+1], k is even
    for (i = 0; i < n - 1; i += 2)
    {
        if (A[i] != A[i + 1])
        {
            *res = A[i];
            return 0;
        }
    }
    if (i == n - 1)
    {
        *res = A[i];
        return 0;
    }
    return -1;
    /*
        int l= 0, mid = 0, r = n-1;
        while(l<r)
        {
            mid = (l+r)/2;
            if(A[mid] == A[mid-1])
            {
                if((mid-l+1) % 2 == 0 )
                    l = mid+1;
                else
                    r = mid-2;
            }
            else if(A[mid] == A[mid+1])
            {
                if((r-mid+1) % 2 == 0 )
                    r = mid - 1;
                else
                    l = mid + 2;
            }
            else break;
        }
        if(r<=l)
        printf("%lld\n", A[l]);
        else
        printf("%lld\n",A[mid]);
    */
}

void heapify(size_t i, size_t k)
{
    size_t l, r, min;
    while (1)
    {
        l = 2 * i + 1; r = 2 * i + 2;
        min = i;
        if (l < k)
            min = aux[l] < aux[min] ? l : min;
        if (r < k)
            min = aux[r] < aux[min] ? r : min;
        if (min == i) break;
        else
        {
            int temp = aux[i];
            aux[i] = aux[min];
            aux[min] = temp;
            i = min;
        }
    }
    //for(int i=0;i<k;i++)
     //printf("%d ",A[i]);
    //printf("\n");
}

///
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
///
int kth_largest_element_in_a_stream(int A[], size_t n, size_t k, int* res,
                                     size_t *res_size)
{
    int in = 0;
    *res_size = 0;

    // loop invariant : res[*res_size] is kth largest value in range A[0, i]
    for (size_t i = 0; i < n; i++)
    {
        in = A[i];
        if (i < k - 1) {
            aux[i] = in;
            res[*res_size] = -1;
        }
        else if (i == k - 1)
        {
            aux[i] = in;
            size_t x = (k - 1) / 2;
            while (x < UINT_MAX)
            {
                heapify(x, k);
                --x;
            }
            res[*res_size] = aux[0];
        }
        else
        {
            if (in > aux[0])
            {
                aux[0] = in;
                heapify(0, k);
            }
            res[*res_size] = aux[0];
        }
        ++*res_size;
    }

    return 0;
}

size_t lb(int *A, size_t n, int val)
{
    size_t l = 0, r = n - 1;
    size_t mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (A[mid] < val)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

///
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
///
int relative_sorting(int A[], size_t n, int B[],  size_t m,
                     int* res, size_t* res_size)
{
    // initialise auxiliury array
    for(size_t i = 0; i < n; i++)
        aux[i] = 0;

    qsort(A, n, sizeof(int), cmp);

    // loop invariant : range res(0, *res_size) contains all duplicates
    // of elements in range B[0, i] in array A
    int k;
    *res_size = 0;
    for (size_t i = 0; i < m; i++)
    {
        k = B[i];
        size_t l = lb(A, n, k);
        while (A[l] == k)
        {
           res[*res_size] = k;
           aux[l] = 1;
           l++; ++*res_size;
        }
    }

    // loop invariant : res(*res_size', *res_size) contains elements in
    // range A(0, i) except for elements already in res
    for (size_t i = 0; i < n; i++)
    {
        if (aux[i] == 0)
        {
            res[*res_size] = A[i];
            ++*res_size;
        }
    }
    return 0;
}


///
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
///
int spirally_traversing_a_matrix(int A[], size_t m, size_t n,
                                 int* res, size_t* res_size)
{
    size_t l = 0, t = 0;
    size_t r = n - 1, b = m - 1;
    *res_size = 0;

    // loop invariant : *res_size increases
    // if t == b  by r - l
    // if r == l  by b - t
    // else by 2*(r-l + b-t - 1)
    while (l <= r && t <= b)
    {
        for (size_t i = l; i <= r; i++)
        {
            res[*res_size] = A[t*n + i];
            ++*res_size;
        }
        for (size_t i = t + 1; i <= b; i++)
        {
            res[*res_size] = A[i*n + r];
            ++*res_size;
        }
        if (t != b) {
            for (size_t i = r - 1; i >= l && i < UINT_MAX; i--)
            {
                res[*res_size] = A[b*n + i];
                ++*res_size;
            }
        }
        if (l != r) {
            for (size_t i = b - 1; i > t; i--)
            {
                res[*res_size] = A[i*n + l];
                ++*res_size;
            }
        }
        l++; r--; t++; b--;
    }
    return 0;
}


///
/// \brief sorts by frequency in \f$O(n)\f$ time using \f$O(n)\f$ auxiliury
/// space.
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
///
int sorting_array_elements_by_frequency(int A[], size_t n, int* res,
                                        size_t* res_size)
{
    // initialise auxiliury array
    for(size_t i = 0; i < n; i++)
        aux[i] = 0;

    // loop invariant : i = sum(aux[loc[0]]..aux[loc[j]])
    int k;
    size_t j = 0;
    for (size_t i = 0; i < n; i++)
    {
        k = A[i];
        if (aux[k] == 0)
            loc[j++] = k;
        aux[k]++;
    }

    // sort loc by frequency of elements
    qsort(loc, j, sizeof(int), cus_cmp);

    // loop invariant : n - *res_size = sum(aux[loc[0]]..aux[loc[j]])
    *res_size = 0;
    for (size_t i = 0; i < j; i++)
        while (aux[loc[i]]) {
            res[*res_size] = loc[i];
            aux[loc[i]]--;
            ++*res_size;
        }

    return 0;
}


int cus_cmp2(const void* a, const void* b)
{
    char buf1[10], buf2[10];
    const struct arr* ia = (const struct arr *)a;
    const struct arr* ib = (const struct arr *)b;
    strcpy(buf1, ia->a);
    strcat(buf1, ib->a);
    strcpy(buf2, ib->a);
    strcat(buf2, ia->a);
    return strcmp(buf2, buf1);
}

///
/// uses sorting to solve in \f$O(n^2)\f$ time using \f$O(n)\f$ auxiliury
/// space.
///
///
/// \param As
/// \param n
/// \return
///
int largest_number_formed_by_array(struct arr As[], size_t n,
                                   char *res, size_t *res_size)
{

    qsort(As, n, sizeof(struct arr), cus_cmp2);
    strcpy(res, As[0].a);
    for(size_t i =1; i < n; i++)
        strcat(res, As[i].a);
    *res_size = strlen(res);
    return 0;
}

/// \}
