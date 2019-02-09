#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "dessPatConfig.h"

#ifdef GOF
#include "gof.h"
#include "mazegame.h"
#include "mazefactory.h"
#include "mazebuilder.h"
#endif

#ifdef GFG
#include "gfg.h"
#endif

#ifdef LCTHW
#include "lcthw.h"
#endif

#ifdef CS180
#include "cs180.h"
#endif

int main (int argc, char *argv[])
{
    fprintf(stdout,"%s Version %d.%d\n",
              argv[0],
              dessPat_VERSION_MAJOR,
              dessPat_VERSION_MINOR);

#ifdef GOF
    {
        auto mg = std::make_unique<MazeGame>();
        mg->CreateMaze(Mazefactory::Instance());
    }
#endif

#ifdef CS180
    {
        std::cout << "stable matching algo :" << std::endl;
        stable_matching();
    }
#endif
#ifdef GFG
  //get number of test cases
  int t, scn;;
  int A[1010]; int B[1010];
  printf("maximum_subarray : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      printf("%d\n", maximum_subarray(A, n));
  }
  printf("find_missing_number : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      printf("%d\n", find_missing_number(A, n));
  }
  printf("subarry_with_given_sum : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      int s; scn = scanf("%d", &s);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      subarry_with_given_sum(A, n, s);
  }
  printf("sort 0 1 2 : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      sort_012(A, n);
  }
  printf("equilibrium point : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      equilibrium_point(A, n);
  }
  printf("maximum sum increasing subsequence : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      maximum_sum_increasing_subsequence(A, n);
  }
  printf("leaders in an array : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      leaders_in_an_array(A, n);
  }
  printf("no of platforms : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &B[i]);
      minimum_platforms(A, B, n);
  }
  printf("maximums_of_subarray_size_k : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      int k; scn = scanf("%d", &k);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      maximums_of_subarray_size_k(A, n, k);
  }
  printf("reverse_array_in_groups : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      int k; scn = scanf("%d", &k);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      reverse_array_in_groups(A, n, k);
  }
  printf("kth_smallest_element : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      int k; scn = scanf("%d", &k);
      kth_smallest_element(A, n, k);
  }
  printf("trapping_rainwater : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      trapping_rainwater(A, n);
  }
  printf("pythagorean_triplet : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      pythagorean_triplet(A, n);
  }
  printf("chocolate_distribution : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      int m; scn = scanf("%d", &m);
      chocolate_distribution(A, n, m);
  }
#endif // GFG

#ifdef LCTHW
  printf("Exercise 1:\n");
  ex1(argc,argv);
  printf("Exercise 3:\n");
  ex3(argc, argv);
  printf("Exercise 7:\n");
  ex7(argc, argv);
  printf("Exercise 8:\n");
  ex8(argc, argv);
  printf("Exercise 9:\n");
  ex9(argc, argv);
  printf("Exercise 10:\n");
  ex10(argc, argv);
  printf("Exercise 11:\n");
  ex11(argc, argv);
  printf("Exercise 12:\n");
  ex12(argc, argv);
  printf("Exercise 13:\n");
  ex13(argc, argv);
  printf("Exercise 14:\n");
  ex14(argc, argv);
  printf("Exercise 15:\n");
  ex15(argc, argv);
  printf("Exercise 16:\n");
  ex16(argc, argv);
  printf("Exercise 17:\n");
  //ex17(argc, argv);
  printf("Exercise 18:\n");
  ex18(argc, argv);
  printf("Exercise 19:\n");
  ex19(argc, argv);
  printf("Exercise 22:\n");
  ex22(argc, argv);
#endif
  return 0;
}
