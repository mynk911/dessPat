/// \file gfg.c
/// \brief this file contains implementations to some coding problems I am
/// working on.
///
/// I am putting together this file to keep track of problems I have solved as
/// well as a reference when I need a quick brush up of common topics. In this
/// file I include the underlying algorithms used to solve problems as well as
/// relevent references.

#include <limits.h>
#include <stdio.h>
#include "gfg.h"

///
/// find the maximum sum contiguous subarray in a given array using the kadane's
/// algorithm which is an O(n) solution to the problem with O(1) auxiliury space.
/// https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
///
int maximum_subarray(int A[], int n)
{
    int maxSoFar = INT_MIN, maxAtIndex = 0, temp = 0;
    for (int index = 0; index<n; index++) {
        //get max for subarray that ends at index
        temp = maxAtIndex + A[index];
        maxAtIndex = temp < A[index] ? A[index] : temp;
        //update global max
        if (maxSoFar < maxAtIndex) {
            maxSoFar = maxAtIndex;
        }
    }

    return maxSoFar;
}


/// uses property of XOR to find missing number.
int find_missing_number(int A[], int n)
{
    /// Calculate X = XOR of first n+1 natural numbers
    int X = 0;
    for(int i = 1; i <= n+1; i++)
        X ^= i;

    /// Calculate Y = XOR of all numbers in array
    int Y = 0;
    for(int i = 0;i < n; i++)
        Y ^= A[i];

    /// return X^Y = missing number
    return X^Y;
}

/*!
 * \brief subarry_with_given_sum
 * \param A
 * \param n
 * \param s
 * \return
 */
void subarry_with_given_sum(int A[], int n, int s)
{
    int start=0, end=0, curr = 0;
    while(start<n)
    {
        if(curr == s) break;
        else if(curr < s && end<n) curr+=A[end++];
        else curr-=A[start++];
    }
    if(curr == s) printf("%d %d\n",start+1,end);
    else printf("-1\n");
}

swap(int A[], int a, int b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

void sort_012(int A[], int n)
{
    int b = 0, m = 0, e = n;
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
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void equilibrium_point(int A[], int n)
{
    if (n == 1) { printf("%d\n", 1); }
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    int sl = 0, sr = sum - A[0];
    int i;
    for (i = 1; i < n; i++)
    {
        sl += A[i - 1];
        sr -= A[i];
        if (sl == sr)
        {
            printf("%d\n", i + 1);
            break;
        }
    }
    if (i == n && n != 1) printf("-1\n");
}

int dp[1010];

void maximum_sum_increasing_subsequence(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dp[i] = A[i];
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[i] < dp[j] + A[i])
            {
                dp[i] = dp[j] + A[i];
            }
        }
    }
    int max_sum = dp[0];
    for (int i = 1; i < n; i++)
    {
        if (dp[i] > max_sum)
        {
            max_sum = dp[i];
        }
    }
    printf("%d\n", max_sum);
}

void leaders_in_an_array(int A[], int n)
{
    int i = 0;
    dp[i] = n - 1;
    for (int j = n - 2; j >= 0; j--)
    {
        if (A[j] >= A[dp[i]])
        {
            i++;
            dp[i] = j;
        }
    }
    while (i > -1)
    {
        printf("%d " , A[dp[i]]);
        i--;
    }
    printf("\n");
}

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int rev_cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

void minimum_platforms(int A[], int B[], int n)
{
    qsort(A, n, sizeof(int), cmp);
    qsort(B, n, sizeof(int), cmp);

    int count = 0, res = 1;
    int i = 0, j = 0;
    while (i < n && j < n)
    {
        if (A[i] < B[j])
        {
            count++; i++;
            if (count > res) res = count;
        }
        else
        {
            count--; j++;
        }
    }
    printf("%d\n", res);
}

void maximums_of_subarray_size_k(int A[], int n, int k)
{
    int  maxpos = -1;
    for (int i = 0, j = k - 1; j < n; j++, i++)
    {
        if (maxpos < i)
        {
            maxpos = i;
            for (int l = i + 1; l <= j; l++)
                if (A[l] > A[maxpos]) maxpos = l;
        }
        else
        {
            if (A[j] > A[maxpos])
                maxpos = j;
        }
        printf("%d ", A[maxpos]);
    }
    printf("\n");
}

void reverse_array_in_groups(int A[], int n, int k)
{
    for (int i = 0; i < n; i += k)
    {
        int l = i, r = (i + k - 1 < n) ? i + k - 1 : n - 1;
        while (l < r)
        {
            long long temp;
            temp = A[l];
            A[l] = A[r];
            A[r] = temp;
            l++; r--;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void kth_smallest_element(int A[], int n, int k)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (A[j] < A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    printf("%d\n", A[n - k]);
}

void trapping_rainwater(int A[], int n)
{
    int l = 0, r = n - 1;
    int maxl = 0, maxr = 0;
    long long water = 0;
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
    printf("%lld\n", water);
}

void pythagorean_triplet(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        A[i] *= A[i];
    }
    //reverse sort : largest to smallest
    qsort(A, n, sizeof(int), rev_cmp);
    int flag = 0;
    for (int i = 0; i < n - 2; i++)
    {
        int l = i + 1, r = n - 1;
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
    if (flag == 1) printf("Yes\n");
    else printf("No\n");
}

void chocolate_distribution(int A[], int n, int m)
{
    qsort(A, n, sizeof(int), cmp);

    int l = 0, r = m - 1;
    int mindiff = INT_MAX;
    while (r < n)
    {
        if (A[r] - A[l] < mindiff)
            mindiff = A[r] - A[l];
        l++, r++;
    }
    printf("%d\n", mindiff);
}
