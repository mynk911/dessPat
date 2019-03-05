#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "dessPatConfig.h"
#include "dbg.h"

#ifdef GOF
#include "gof.h"
#include "mazegame.h"
#include "mazefactory.h"
#include "mazebuilder.h"
#include "textshape.h"
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
        auto mg = std::make_shared<gof::creational::MazeGame>();
        mg->CreateMaze(gof::creational::Mazefactory::Instance());

        auto sp = std::make_unique<gof::structural::Shape>(1,2,4,5);
        gof::structural::Point a(0,0), b(0,0);
        sp->BoundingBox(&a,&b);
        debug("sp a:%f %f,b:%f %f",a.getX(),a.getY(), b.getX(), b.getY());
        auto mp = sp->CreateManipulator();
        auto tv = std::make_unique<gof::structural::Textview>(1,3,4,7);
        auto tsp = std::make_unique<gof::structural::TextShape>(1,2,4,5);
    }
#endif

#ifdef CS180
    {
        std::cout << "stable matching algo :" << std::endl;
        cs180::stable_matching();
        cs180::pq::heap<int> pq;
        pq.insert(5, 1);
        pq.insert(4, 8);
        pq.insert(2, 2);
        pq.insert(1, 4);
        pq.insert(3, 3);
        pq.insert(7, 5);
        pq.changeKey(0, 25);
        for(int i = 0;i < 6;i++)
            std::cout << pq.extractmin() << " ";
        std::cout << "\n";
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
  printf("stock_buy_and_sell : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      stock_buy_and_sell(A, n);
  }
  printf("elements_with_left_side_smaller_and_right_side_greater : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      elements_with_left_side_smaller_and_right_side_greater(A, n);
  }
  printf("convert_array_into_zigzag_fashion : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      convert_array_into_zigzag_fashion(A, n);
  }
  printf("find_the_element_that_appears_once_in_sorted_array : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      find_the_element_that_appears_once_in_sorted_array(A, n);
  }
  printf("kth_largest_element_in_a_stream : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int k; scn = scanf("%d", &k);
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      kth_largest_element_in_a_stream(A, n,k);
  }
  printf("relative_sorting : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      int m; scn = scanf("%d", &m);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%d", &A[i]);
      for (int i = 0; i < m; i++)
          scn = scanf("%d", &B[i]);
      relative_sorting(A, B, n, m);
  }
  printf("spirally_traversing_a_matrix : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int m; scn = scanf("%d", &m);
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < m; i++)
          for(int j = 0; j < n; j++)
          scn = scanf("%d", &A[n*i + j]);
      spirally_traversing_a_matrix(A, m, n);
  }
  printf("sorting_array_elements_by_frequency : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
              scn = scanf("%d", &A[i]);
      sorting_array_elements_by_frequency(A, n);
  }
  struct arr As[105];
  printf("largest_number_formed_by_array : \n");
  scn = scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scn = scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scn = scanf("%s", As[i].a);
      largest_number_formed_by_array(As, n);
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
  printf("Exercise 23:\n");
  ex23(argc, argv);
  printf("Exercise 24:\n");
  ex24(argc, argv);
  printf("Exercise 25:\n");
  ex25(argc, argv);
#endif
  return 0;
}
