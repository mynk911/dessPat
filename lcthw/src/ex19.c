///
/// \file ex19.c
/// \brief ex 19 debug macros
/// \author Mayank Bansal
///

#include <stdlib.h>
#include <stdio.h>

#include "dbg.h"
#include "lcthw.h"
int test_check(char* file_name)
{
    FILE* input = NULL;
    char* block = NULL;

    block = malloc(100);
    check_mem(block);

    input = fopen(file_name, "r");
    check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) fclose(input);
    return -1;
}

int test_sentinel(int code)
{
    char* temp = malloc(100);
    check_mem(temp);

    switch (code)
    {
    case 1 :
        log_info("it worked.");
        break;
    default:
        sentinel("I shouldn't run.");
    }

    free(temp);
    return 0;

error:
    if (temp)
        free(temp);
    return -1;
}

int test_check_mem()
{
    char* test = NULL;
    check_mem(test);

    free(test);
    return 0;
error:
    return -1;
}

int test_check_debug()
{
    int i = 0;
    check_debug(i != 0, "Oops I was zero.");
    return 0;
error:
    return -1;
}

int ex19(int argc, char *argv[])
{
    check(argc > 2, "Need an argument.");

    debug("I have brown hair.");
    debug("I am %d years old.", 24);
    log_err("I believe everything is broken");
    log_err("There are %d problems im %s", 0, "space");
    log_warn("You can safely ignore this");
    log_warn("Maybe Consider looking at %s.", "/etc/passwd");
    log_info("Well I did something mundane");
    log_info("It happened %f times today", 1.3f);

    check(test_check("CMakeCache.txt") == 0, "failed with ex19.c");
    check(test_check(argv[1]) == -1, "failed with argv");
    check(test_sentinel(1) == 0, "test_sentinel failed");
    check(test_sentinel(100) == -1, "test_sentinel failed");
    check(test_check_mem() == -1, "test_check_mem failed");
    check(test_check_debug() == -1, "test_check_debug failed");

    return 0;
error:
    return 1;
}