#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "dessPatConfig.h"
#include "gtest/gtest.h"

int main (int argc, char *argv[])
{
    fprintf(stdout,"%s Version %d.%d\n",
              argv[0],
              dessPat_VERSION_MAJOR,
              dessPat_VERSION_MINOR);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  return 0;
}
