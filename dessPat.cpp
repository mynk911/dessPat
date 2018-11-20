#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int main (int argc, char *argv[])
{
    fprintf(stdout,"%s Version %d.%d\n",
              argv[0],
              dessPat_VERSION_MAJOR,
              dessPat_VERSION_MINOR);

#ifdef GOF
    {
        auto mg = std::make_unique<MazeGame>();
        mg->CreateMaze(mg->MakePrototypeFactory());
    }
#endif

#ifdef GFG
  //get number of test cases
  int t, scn;;
  int A[1010];
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
#endif
  return 0;
}
