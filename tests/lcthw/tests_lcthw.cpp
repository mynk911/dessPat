#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "cmath"

#include "gtest/gtest.h"

#include "dessPatConfig.h"
#include "dbg.h"

#include "bstrlib.h"
#include "lcthw.h"
#include "ex17_ds.h"

#ifdef C_SERVICE_MOCK_TESTS
#include "ServicesMocks.h"
#include "FakeServices.h"

class LcthwServiceMockTest : public ::testing::Test
{
public:
    LcthwServiceMockTest()
    {
	_libc.reset(new ::testing::NiceMock<LibcService>());
    }

    ~LcthwServiceMockTest()
    {
	_libc.reset();
    }
    static std::unique_ptr<LibcService> _libc;
};

std::unique_ptr<LibcService> LcthwServiceMockTest::_libc;

LibcService::~LibcService()
{

}

extern "C" void* my_malloc(size_t size)
{
    return LcthwServiceMockTest::_libc->malloc(size);
}

extern "C" FILE* my_fopen(const char* filename, const char* modes)
{
    return LcthwServiceMockTest::_libc->fopen(filename, modes);
}
#endif // C_SERVICE_MOCK_TESTS


class LcthwTest : public  ::testing::Test
{
protected:
    LcthwTest()
	: out_test(fopen("lcthw_gtest.txt", "w+"))
    {}

    ~LcthwTest()
    {
	fclose(out_test);
    }

    FILE* out_test;
    static char buf[1040];
};

char LcthwTest::buf[1040];

TEST_F(LcthwTest, ex1)
{
    int a = ex1(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You are 100 miles away.\n");
}

TEST_F(LcthwTest, ex3)
{
    int a = ex3(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "I am 23 years old.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "I am 74 inches tall.\n");
}

TEST_F(LcthwTest, ex7)
{
    int a = ex7(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You are 100 miles away.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You have 2.345000 levels of power.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You have 56789.453200 awesome super powers.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "I have an initial A.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "I have a first name Zed.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "I have a last name Shaw.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "My whole name is Zed A Shaw.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You have 100 bugs at the imaginary rate of 1.200000.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "The entire universe has 1073741824 bugs.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You are expected to have 120.000000 bugs.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "That is only a 1.117587e-07 portion of the universe.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf,  "Which means you should care 0%.\n");
}

TEST_F(LcthwTest, ex8NoArg)
{
    int argc = 1;
    const char *argv[] = {"test"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You only have one argument. You suck.\n");
}

TEST_F(LcthwTest, ex8Arg)
{
    int argc = 2;
    const char *argv[] = {"test", "here it is"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Here's your arguments:\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "test here it is ");
}

TEST_F(LcthwTest, ex8TooManyArgs)
{
    int argc = 4;
    const char *argv[] = {"test", "here it is", "tease", "fried"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "You have too many arguments. You suck.\n");
}

TEST_F(LcthwTest, ex9)
{
    int a = ex9(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 \n");
}

TEST_F(LcthwTest, ex10NoArgs)
{
    int argc = 1;
    const char *argv[] = {"test"};
    int a = ex10(argc, argv, out_test);
    EXPECT_EQ(a, 1);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "ERROR: You need one argument.\n" );
}

TEST_F(LcthwTest, ex10Args)
{
    int argc = 2;
    const char *argv[] = {"test", "uyYaieyobDOYEIAU"};
    int a = ex10(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "0: 'U'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "3: 'A'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "4: 'I'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "5: 'E'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "6: 'Y'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "7: 'O'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "8: b is not a vowel\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "9: D is not a vowel\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "10: 'O'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "11: 'Y'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "12: 'E'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "13: 'I'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "14: 'A'\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "15: 'U'\n" );
}

TEST_F(LcthwTest, ex11)
{
    int a = ex11(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "numbers: 0 0 0 0\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name each: 97 0 0 0\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name each: y Z D a\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name each: \xFF \xFF \xFF \xFF\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name: a\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "numbers: 1 2 3 4\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name each: Z e d " );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name: Zed\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "another: Zed\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "another each: Z e d " );
}

TEST_F(LcthwTest, ex12)
{
    int a = ex12(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf2[255];
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    sprintf(buf2, "The size of an int: %zu\n", sizeof(int));
    EXPECT_STREQ(buf, buf2);
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    sprintf(buf2, "The size of areas (int[]): %zu\n", sizeof(int)*5);
    EXPECT_STREQ(buf, buf2);
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "The number of ints in areas: 5\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "The first area is 10, the 2nd 12.\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    sprintf(buf2, "The size of a char: %zu\n", sizeof(char));
    EXPECT_STREQ(buf, buf2 );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    sprintf(buf2, "The size of name (char[]): %zu\n", sizeof(char)*4);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, buf2);
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "The number of chars: 4\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    sprintf(buf2,"The size of full_name (char[]): %zu\n", sizeof(char)*12);
    EXPECT_STREQ(buf, buf2 );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "The number of chars: 12\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "name=\"Zed\" and full_name=\"Zed A. Shaw\"\n" );
}

TEST_F(LcthwTest, ex13)
{
    int argc = 3;
    const char *argv[] = {"test", "hey", "there"};
    int a = ex13(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "arg 1: hey\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "arg 2: there\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "state 0: California\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "state 1: Oregon\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "state 2: Washington\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "state 3: Texas\n" );
}

TEST_F(LcthwTest, ex14)
{
    int argc = 3;
    const char *argv[] = {"test", "bruce wills", "bruce123 wills#%!"};
    int a = ex14(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "test\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "bruce wills\n" );
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "bruce wills\n" );
}

TEST_F(LcthwTest, ex15)
{
    int a = ex15(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "---\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "---\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "---\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
}

TEST_F(LcthwTest, ex16)
{
    struct Person* joe = CreatePerson("Joe Frank", 32, 64,140);
    EXPECT_NE(joe, nullptr);
    PrintPerson(out_test, joe);
    fseek(out_test, 0, SEEK_SET);
    char* res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Name : Joe Frank\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Age : 32\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Height : 64\n");
    res = fgets(buf, 255, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "Weight : 140\n");
    DestroyPerson(&joe);
    EXPECT_EQ(joe, nullptr);
}

using LcthwDeathTest = LcthwTest;

TEST_F(LcthwDeathTest, ex17InSufficientArguments)
{
    errno = 0;
    int argc = 2;
    const char *argv[] = {"ex17", "test_dbFile"};
    EXPECT_EXIT(ex17(argc, argv, buf), ::testing::ExitedWithCode(1),
		"USAGE: dessPat <dbfile> <action> ");
}

#ifdef C_SERVICE_MOCK_TESTS
using LcthwServiceMockDeathTest = LcthwServiceMockTest;
TEST_F(LcthwServiceMockDeathTest, ex17MallocFail1)
{
    EXPECT_CALL(*(LcthwServiceMockTest::_libc), malloc(::testing::_))
				       .WillRepeatedly(::testing::Return(nullptr));
    errno = ENOMEM;
    ::testing::Mock::AllowLeak((LcthwServiceMockTest::_libc).get());
    int argc = 3;
    const char *argv[] = {"ex17", "test_dbFile", "c"};
    char buf[100];
    EXPECT_EXIT(ex17(argc, argv, buf), ::testing::ExitedWithCode(1),
		"Cannot create Connection");
}
#endif // C_SERVICE_MOCK_TESTS

TEST_F(LcthwDeathTest, ex17TryingToReadNonExistentDatabaseFile)
{
    errno = 0;
    int argc = 4;
    const char *argv[] = {"ex17", "test_gtsgserufldfjnaku", "g"};
    EXPECT_EXIT(ex17(argc, argv, buf), ::testing::ExitedWithCode(1),
	       "failed to open file");
}

TEST_F(LcthwDeathTest, ex17InvalidRecordNumber)
{
    errno = 0;
    int argc = 4;
    auto s = std::to_string(MAX_ROWS);
    const char *argv[] = {"ex17", "test_dbFile", "c", s.c_str()};
    EXPECT_EXIT(ex17(argc, argv, buf), ::testing::ExitedWithCode(1),
	       "there are not that many records");
}

TEST_F(LcthwDeathTest, databaseFileDoesNotExist)
{
    errno = 0;
    int argc = 4;
    const char *argv[] = {"ex17", "aslifghwgwhwgrwn", "g", "1"};
    EXPECT_EXIT(ex17(argc, argv, buf), ::testing::ExitedWithCode(1),
	       "failed to open file");
}

TEST_F(LcthwTest, ex17CRUDTest)
{
    errno = 0;
    const char *command = "ex17", *file = "ex17Crudtest.txt";
    const char modes[] = {'c', 'g', 's', 'd', 'l'};
    const char *argv[10];
    argv[0] = command;
    argv[1] = file;
    argv[2] = &modes[0];
    int argc = 3;
    ex17(argc, argv, buf);

    argv[2] = &modes[2];
    argv[3] = "0";
    argv[4] = "Red";
    argv[5] = "red@blue.mail";
    argc = 6;
    ex17(argc, argv, buf);

    argv[2] = &modes[1];
    argc = 4;
    ex17(argc, argv, buf);
    EXPECT_STREQ(buf, "0 Red red@blue.mail\n");

    argv[2] = &modes[2];
    argv[3] = "1";
    argv[4] = "Black";
    argv[5] = "black@blue.mail";
    argc = 6;
    ex17(argc, argv, buf);

    argv[2] = &modes[1];
    argc = 4;
    ex17(argc, argv, buf);
    EXPECT_STREQ(buf, "1 Black black@blue.mail\n");

    argv[2] = &modes[4];
    argc = 3;
    ex17(argc, argv, buf);
    EXPECT_STREQ(buf, "0 Red red@blue.mail\n1 Black black@blue.mail\n");

    argv[2] = &modes[3];
    argv[3] = "0";
    argc = 4;
    ex17(argc, argv, buf);
    argv[2] = &modes[4];
    argc = 3;
    ex17(argc, argv, buf);
    EXPECT_STREQ(buf, "1 Black black@blue.mail\n");

    argv[2] = &modes[2];
    argv[3] = "0";
    argv[4] = "Yellow";
    argv[5] = "yellow@blue.mail";
    argc = 6;
    ex17(argc, argv, buf);

    argv[2] = &modes[4];
    argc = 3;
    ex17(argc, argv, buf);
    EXPECT_STREQ(buf, "0 Yellow yellow@blue.mail\n1 Black black@blue.mail\n");
}

int ex18(int argc,const char** argv, char* buf, sort_cb sort, compare_cb cmp)
{
    int count = argc - 1;
    const char** inputs = argv + 1;

    int* numbers =(int *) malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++)
	numbers[i] = atoi(inputs[i]);

    int *sorted = sort(numbers, count, cmp);

    int length  = 0;
    for (int i = 0; i < count; i++)
	length += sprintf(buf + length, "%d ", sorted[i]);
    length += sprintf(buf + length, "\n");

    free(sorted);
    free(numbers);

    return 0;
}

TEST_F(LcthwTest, ex18BubbleSort)
{
    int argc = 6;
    const char* argv[] = {"dessPat", "4", "1", "3", "5", "2"};
    ex18(argc, argv, buf, bubble_sort, sorted_order);
    EXPECT_STREQ(buf, "1 2 3 4 5 \n");

    ex18(argc, argv, buf, bubble_sort, reversed_order);
    EXPECT_STREQ(buf, "5 4 3 2 1 \n");

    ex18(argc, argv, buf, bubble_sort, strange_order);
    EXPECT_STREQ(buf, "4 5 3 2 1 \n");
}

TEST_F(LcthwTest, ex18SelectionSort)
{
    int argc = 6;
    const char* argv[] = {"dessPat", "4", "1", "3", "5", "2"};
    ex18(argc, argv, buf, selection_sort, sorted_order);
    EXPECT_STREQ(buf, "1 2 3 4 5 \n");

    ex18(argc, argv, buf, selection_sort, reversed_order);
    EXPECT_STREQ(buf, "5 4 3 2 1 \n");

    ex18(argc, argv, buf, selection_sort, strange_order);
    EXPECT_STREQ(buf, "2 4 5 3 1 \n");
}

TEST_F(LcthwTest, ex19)
{
    EXPECT_EQ(test_check("CMakeCache.txt"), 0);
    EXPECT_EQ(test_check("TRUMPER") , -1);
    EXPECT_EQ(test_sentinel(1) , 0);
    EXPECT_EQ(test_sentinel(100) , -1);
    EXPECT_EQ(test_check_mem() , -1);
    EXPECT_EQ(test_check_debug() , -1);
}

TEST_F(LcthwTest, ex22)
{
    // get pointer to static variable THE_AGE in ex22.h
    // and modify it
    int* x = age();
    *x = 25000;
    EXPECT_EQ(25000, get_age());

    // change static global variable THE_AGE via exposed API
    set_age(100);
    EXPECT_EQ(100, get_age());

    // can set global variable THE_SIZE directly
    EXPECT_EQ(get_size(), 1000);
    THE_SIZE = 9;
    EXPECT_EQ(get_size(), 9);

    // local static variable ratio  retain values even when function
    // exits
    EXPECT_EQ(update_ratio(2.0), 1.0);
    EXPECT_EQ(update_ratio(10.0), 2.0);

    int count = 4;
    scope_demo(count * 20);
    //pass by value hence count should not change
    EXPECT_EQ(count, 4);
}

int valid_copy(char* data, int count, int expects)
{
    int i = 0;
    for(i = 0; i < count; i++)
    {
	if (data[i] != expects) {
	    log_err("[%d] %c != %c", i, data[i], expects);
	    return -1;
	}
    }
    return 0;
}

TEST_F(LcthwTest, ex23NormalCopy)
{
    char from[1000] = { 'a' };
    char to[1000] = { 'c' };
    int rc = 0;

    memset(from, 'x', 1000);
    memset(to, 'y', 1000);

    EXPECT_EQ(valid_copy(to, 1000, 'y'), 0);
    rc = normal_copy(from, to, 1000);
    EXPECT_EQ(rc , 1000);
    EXPECT_EQ(valid_copy(to, 1000, 'x'), 0);
}

TEST_F(LcthwTest, ex23DuffsDevice)
{
    char from[1000] = { 'a' };
    char to[1000] = { 'c' };
    int rc = 0;

    memset(from, 'x', 1000);
    memset(to, 'y', 1000);

    EXPECT_EQ(valid_copy(to, 1000, 'y'), 0);
    rc = duffs_device(from, to, 1000);
    EXPECT_EQ(rc , 1000);
    EXPECT_EQ(valid_copy(to, 1000, 'x'), 0);
}

TEST_F(LcthwTest, ex24Test)
{
    FILE* in = fopen("ex24_input.txt", "w");
    fprintf(in, "Derek\nBrian\n27 2 35000");
    fclose(in);
    in = fopen("ex24_input.txt","r");
    ex24(in, out_test);
    fseek(out_test, 0, SEEK_SET);

    char* res = fgets(buf, 512, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, "you : Derek\n");

    res = fgets(buf, 512, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, " Brian\n");

    res = fgets(buf, 512, out_test);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(buf, " 27 Green 35000.000000\n");

    fclose(in);
}

TEST_F(LcthwTest, ex25Test)
{
    FILE* in = fopen("ex24_input.txt", "w");
    fprintf(in, "Derek\nOBrian\n27235000\n");
    fclose(in);
    in = fopen("ex24_input.txt","r");
    char* first_name = NULL;
    char initial = ' ';
    char* last_name = NULL;
    int age = 0;

    int rc = read_scan(in, "%s", MAX_DATA, &first_name);
    ASSERT_EQ(rc, 0);
    EXPECT_STREQ(first_name, "Derek\n");

    rc = read_scan(in, "%c", &initial);
    ASSERT_EQ(rc, 0);
    EXPECT_EQ(initial, 'O');

    rc = read_scan(in, "%s", MAX_DATA, &last_name);
    ASSERT_EQ(rc, 0);
    EXPECT_STREQ(last_name, "Brian\n");

    rc = read_scan(in, "%d", &age);
    ASSERT_EQ(rc, 0);
    EXPECT_EQ(age, 27235000);

    free(first_name);
    free(last_name);

    fclose(in);
}

class ListTest : public ::testing::Test
{
protected:
    ListTest();
    ~ListTest();

    List* list;
};

ListTest::ListTest()
{
    list = List_create();
}

ListTest::~ListTest()
{
    List_destroy(list);
}

using LcthwListTest = ListTest;

TEST_F(LcthwListTest, pushPopTest)
{
    const char *s1 = "test 1";
    List_push(list, s1);
    EXPECT_STREQ((char*)List_last(list), s1);
    const char *s2 = "test 2";
    List_push(list,s2);
    EXPECT_STREQ((char*)List_last(list), s2);
    const char *s3 = "test 3";
    List_push(list,s3);
    EXPECT_STREQ((char*)List_last(list), s3);
    EXPECT_EQ(List_count(list), 3);

    const char* val = (const char *)List_pop(list);
    EXPECT_STREQ(val, s3) << "wrong value on pop";
    val = (const char *)List_pop(list);
    EXPECT_STREQ(val, s2) << "wrong value on pop";
    val = (const char *)List_pop(list);
    EXPECT_STREQ(val, s1) << "wrong value on pop";
    EXPECT_EQ(List_count(list), 0);
}

TEST_F(LcthwListTest, shiftRemoveUnshiftTest)
{
    const char *s1 = "test 1";
    List_unshift(list, s1);
    EXPECT_STREQ((char*)List_first(list), s1);
    const char *s2 = "test 2";
    List_unshift(list,s2);
    EXPECT_STREQ((char*)List_first(list), s2);
    const char *s3 = "test 3";
    List_unshift(list,s3);
    EXPECT_STREQ((char*)List_first(list), s3);
    EXPECT_EQ(List_count(list), 3);

    const char* val = (const char *)List_remove(list, list->first->next);
    EXPECT_STREQ(val, s2) << "wrong value on remove";
    EXPECT_EQ(List_count(list), 2);
    EXPECT_STREQ((char*)List_first(list), s3);
    EXPECT_STREQ((char*)List_last(list), s1);

    val = (const char *)List_shift(list);
    EXPECT_STREQ(val, s3) << "wrong value on shift";
    val = (const char *)List_shift(list);
    EXPECT_STREQ(val, s1) << "wrong value on shift";
    EXPECT_EQ(List_count(list), 0);
}

bool isSorted(List* words)
{
    LIST_FOREACH(words, first, next, cur)
    {
        if((cur->next != nullptr) &&
           (strcmp(static_cast<const char *>(cur->value),
                   static_cast<const char *>(cur->next->value)) > 0))
        {
            debug("%s %s", static_cast<const char*>(cur->value),
                           static_cast<const char*>(cur->next->value));
            return false;
        }
    }
    return true;
}

TEST_F(LcthwListTest, listBubbleSortTest)
{
    // empty list
    int rc = List_bubble_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_EQ(rc, 0) << "bubble sort failed!!";
    EXPECT_TRUE(isSorted(list)) << "bubble sort fails to sort empty list";

    const char* values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

    for (int i = 0; i < 5; i++)
        List_push(list, values[i]);

    // unsorted list
    rc = List_bubble_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_EQ(rc, 0) << "bubble sort failed!!";
    EXPECT_TRUE(isSorted(list)) << "list is not sorted after bubble sort";

    // sorted list
    rc = List_bubble_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_EQ(rc, 0) << "bubble sort failed!!";
    EXPECT_TRUE(isSorted(list)) << "bubble sort fails for already sorted list";
}

TEST_F(LcthwListTest, listMergeSortTest)
{
    // empty list
    auto res = List_merge_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_TRUE(isSorted(res)) << "merge sort fails to sort empty list";

    const char* values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

    for (int i = 0; i < 5; i++)
        List_push(list, values[i]);

    // unsorted list
    auto res2 = List_merge_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_TRUE(isSorted(res2)) << "list is not sorted after merge sort";

    // sorted list
    auto res3 = List_merge_sort(list, static_cast<ListCompare>(strcmp));
    EXPECT_TRUE(isSorted(res3)) << "merge sort fails for already sorted list";
}

class DArrayTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    DArray* _array;
};

void DArrayTest::SetUp()
{
    _array = DArray_create(sizeof (int), 100);
    ASSERT_NE(_array, nullptr);
    ASSERT_NE(_array->contents, nullptr);
    ASSERT_EQ(_array->end, 0);
    ASSERT_EQ(_array->element_size, sizeof (int));
    ASSERT_EQ(_array->max, 100);
}

void DArrayTest::TearDown()
{
    DArray_destroy(_array);
}

using LcthwDArrayTest = DArrayTest;

TEST_F(LcthwDArrayTest, dArrayNewSetGetRemove)
{
    int* val1, *val2;

    val1 = static_cast<int *>(DArray_new(_array));
    ASSERT_NE(val1, nullptr);
    val2 = static_cast<int *>(DArray_new(_array));
    ASSERT_NE(val2, nullptr);

    DArray_set(_array, 0, val1);
    DArray_set(_array, 1, val2);

    ASSERT_EQ(DArray_get(_array, 0), val1);
    ASSERT_EQ(DArray_get(_array, 1), val2);

    auto checkVal = static_cast<const int *>(DArray_remove(_array, 0));
    ASSERT_NE(checkVal, nullptr);
    ASSERT_EQ(*checkVal, *val1);
    ASSERT_EQ(DArray_get(_array, 0), nullptr);
    DArray_free(const_cast<int *>(checkVal));

    checkVal = static_cast<const int *>(DArray_remove(_array, 1));
    ASSERT_NE(checkVal, nullptr);
    ASSERT_EQ(*checkVal, *val2);
    ASSERT_EQ(DArray_get(_array, 1), nullptr);
    DArray_free(const_cast<int *>(checkVal));
}

TEST_F(LcthwDArrayTest, dArrayExpandContract)
{
    size_t old_max = _array->max;
    DArray_expand(_array);
    ASSERT_EQ(_array->max, old_max + _array->expand_rate);

    DArray_contract(_array);
    ASSERT_EQ(_array->max, _array->expand_rate + 1);

    // max should not fall below minimum value which is expand rate
    DArray_contract(_array);
    ASSERT_EQ(_array->max, _array->expand_rate + 1);
}

TEST_F(LcthwDArrayTest, dArrayPushPop)
{
    for (int i = 0; i < 1000; i++)
    {
        int* val = static_cast<int *>(DArray_new(_array));
        *val = i * 333;
        DArray_push(_array, val);
    }

    ASSERT_EQ(_array->max, 1300);

    for(int i = 999; i >= 0; i--)
    {
        auto val = static_cast<const int *>(DArray_pop(_array));
        ASSERT_NE(val, nullptr);
        ASSERT_EQ(*val, i * 333);
        DArray_free(const_cast<int *>(val));
    }
}

int test_cmp(char* a, char* b)
{
    return strcmp(a, b);
}

int is_sorted(DArray* array)
{
    for(size_t i = 0; i < DArray_count(array)-1; i++) {
        if(strcmp(static_cast<const char *>(DArray_get(array, i)),
                  static_cast<const char *>(DArray_get(array, i+1))) > 0)
            return 0;
    }
    return 1;
}

void test_darray_sort(DArray* array, int(*func)(DArray*, DArray_compare))
{
    const char* words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"};
    for(int i = 0; i < 5; i++)
        DArray_push(array, words[i]);

    int rc = func(array, reinterpret_cast<DArray_compare>(test_cmp));
    ASSERT_EQ(rc, 0);
    ASSERT_EQ(is_sorted(array), 1);
}

TEST_F(LcthwDArrayTest, dArrayQsortTest)
{
    test_darray_sort(_array, DArray_qsort);
}


TEST_F(LcthwDArrayTest, dArrayHsortTest)
{
    test_darray_sort(_array, DArray_hsort);
}

TEST_F(LcthwDArrayTest, dArrayMsortTest)
{
    test_darray_sort(_array, DArray_msort);
}

TEST_F(LcthwTest, ex35VAriantTest)
{
    Variant a_int; a_int.type = TYPE_INT; a_int.data.as_integer = 100;
    Variant a_float; a_float.type = TYPE_FLOAT; a_float.data.as_float = 100.34f;
    Variant a_string; a_string.type = TYPE_STRING; a_string.data.as_string = "Test String!";

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_string);
}

class RadixMapTest : public ::testing::Test
{
protected:
    void makeRandom();
    void checkOrder();
    void SetUp() override;
    void TearDown() override;

    RadixMap* radixMap = nullptr;
};

void RadixMapTest::SetUp()
{
    size_t N = 200;
    radixMap = RadixMap_create(N);
    ASSERT_NE(radixMap, nullptr);
    makeRandom();
}

void RadixMapTest::TearDown()
{
    RadixMap_destroy(radixMap);
}

void RadixMapTest::makeRandom()
{
    for(size_t i = 0; i < radixMap->max - 1; i++)
    {
        uint32_t key = static_cast<uint32_t>(rand() | (rand() << 16));
        ASSERT_EQ(RadixMap_add(radixMap, key, i), 0) << "failed to add key " << key;
    }
}

void RadixMapTest::checkOrder()
{
    RMElement d1, d2;
    unsigned int i = 0;

    for(i = 0; radixMap->end > 0 && i < radixMap->end-1; i++)
    {
        d1 = radixMap->contents[i];
        d2 = radixMap->contents[i+1];

        ASSERT_LE(d1.data.key, d2.data.key);
    }
}

using LcthwRadixMapTest = RadixMapTest;

TEST_F(LcthwRadixMapTest, operationsTest)
{
    RadixMap_sort(radixMap);
    size_t lb;
    checkOrder();
    RMElement *d = nullptr, *found = nullptr;
    for(unsigned int i = radixMap->end / 2; i < radixMap->end; i++)
    {
        d = &radixMap->contents[i];

        found = RadixMap_find(radixMap, d->data.key, &lb);
        ASSERT_NE(found, nullptr);
        ASSERT_EQ(found->data.key, d->data.key);
    }
    checkOrder();

    while(radixMap->end > 0)
    {
        RMElement *el = RadixMap_find(radixMap, radixMap->contents[radixMap->end/2].data.key, &lb);
        ASSERT_NE(el, nullptr);
        size_t old_end = radixMap->end;
        ASSERT_EQ(RadixMap_delete(radixMap, el), 0);
        ASSERT_EQ(old_end - 1, radixMap->end);
        checkOrder();
    }

}

class HashMapTest : public ::testing::Test
{
protected:
    static int traverse_good_cb(HashmapNode* node)
    {
        debug("KEY:%s", bdata((bstring) node->key));
        traverse_called++;
        return 0;
    }

    static int traverse_fail_cb(HashmapNode* node)
    {
        debug("KEY:%s", bdata((bstring) node->key));
        traverse_called++;
        if(traverse_called == 2) return 1;
        return 0;
    }

    static void SetUpTestSuite()
    {
        traverse_called = 0;
        test1 = bsStatic("test data 1");
        test2 = bsStatic("test data 2");
        test3 = bsStatic("test data 3");
        expect1 = bsStatic("THE VALUE 1");
        expect2 = bsStatic("THE VALUE 2");
        expect3 = bsStatic("THE VALUE 3");
    }

    void SetUp() override;
    void TearDown() override;
    Hashmap* map = nullptr;
    static int traverse_called;
    static struct tagbstring test1,test2, test3,
                   expect1, expect2, expect3;
};


struct tagbstring HashMapTest::test1, HashMapTest::test2, HashMapTest::test3,
        HashMapTest::expect1, HashMapTest::expect2, HashMapTest::expect3;
int HashMapTest::traverse_called;
using LcthwHashMapTest = HashMapTest;

void HashMapTest::SetUp()
{
    map = Hashmap_create(nullptr, nullptr);
    ASSERT_NE(map, nullptr) << "failed to create hashmap";
}

void HashMapTest::TearDown()
{
    Hashmap_destroy(map);
}

TEST_F(LcthwHashMapTest, operationsTest)
{
    int rc = Hashmap_set(map, &test1, &expect1);
    ASSERT_EQ(rc, 0) << "failed to set test1";
    bstring result = static_cast<bstring>(Hashmap_get(map, &test1));
    ASSERT_EQ(result, &expect1) << "wrong value for test 1";

    rc = Hashmap_set(map, &test2, &expect2);
    ASSERT_EQ(rc, 0) << "failed to set test2";
    result = static_cast<bstring>(Hashmap_get(map, &test2));
    ASSERT_EQ(result, &expect2) << "wrong value for test 2";

    rc = Hashmap_set(map, &test3, &expect3);
    ASSERT_EQ(rc, 0) << "failed to set test3";
    result = static_cast<bstring>(Hashmap_get(map, &test3));
    ASSERT_EQ(result, &expect3) << "wrong value for test 3";

    rc = Hashmap_traverse(map, traverse_good_cb);
    ASSERT_EQ(rc, 0);
    ASSERT_EQ(traverse_called, 3);

    traverse_called = 0;
    rc = Hashmap_traverse(map, traverse_fail_cb);
    ASSERT_EQ(rc, 1);
    ASSERT_EQ(traverse_called, 2);

    bstring deleted = static_cast<bstring>(Hashmap_delete(map, &test1));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect1);
    result = static_cast<bstring>( Hashmap_get(map, &test1));
    ASSERT_EQ(result, nullptr);

    deleted = static_cast<bstring>( Hashmap_delete(map, &test2));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect2);
    result = static_cast<bstring>( Hashmap_get(map, &test2));
    ASSERT_EQ(result, nullptr);

    deleted = static_cast<bstring>( Hashmap_delete(map, &test3));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect3);
    result = static_cast<bstring>( Hashmap_get(map, &test3));
    ASSERT_EQ(result, nullptr);
}

TEST_F(LcthwHashMapTest, distributionsTest)
{
#define NUM_BUCKETS 100
    uint32_t stats[3][NUM_BUCKETS] = {{0}};

    Hashmap_generate_distribution(Hashmap_fnv1a_hash, stats[0], NUM_BUCKETS);
    Hashmap_generate_distribution(Hashmap_adler32_hash, stats[1], NUM_BUCKETS);
    Hashmap_generate_distribution(Hashmap_djb_hash, stats[2], NUM_BUCKETS);

    FILE* out = fopen("dist.txt", "w");
    for(int i = 0; i < NUM_BUCKETS; i++)
        fprintf(out, "%u %u %u\n", stats[0][i], stats[1][i], stats[2][i]);
    fclose(out);
}

TEST_F(LcthwTest, ex39TestFindAndScan)
{
    struct tagbstring inputString = bsStatic("I have ALPHA beta ALPHA and orange ALPHA");
    struct tagbstring alpha = bsStatic("ALPHA");

    StringScanner *scan = StringScanner_create(&inputString);
    ASSERT_NE(scan, nullptr) << "failed to create scanner";

    int find_i = String_find(&inputString, &alpha);
    ASSERT_GT(find_i, 0);

    int scan_i = StringScanner_scan(scan, &alpha);
    ASSERT_GT(scan_i, 0);

    ASSERT_EQ(find_i, scan_i);

    scan_i = StringScanner_scan(scan, &alpha);
    ASSERT_GT(scan_i, find_i);

    scan_i = StringScanner_scan(scan, &alpha);
    ASSERT_GT(scan_i, find_i);

    StringScanner_destroy(scan);
}

class BSTreeTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite()
    {
        traverse_called = 0;
        test1 = bsStatic("test data 1");
        test2 = bsStatic("test data 2");
        test3 = bsStatic("test data 3");
        expect1 = bsStatic("THE VALUE 1");
        expect2 = bsStatic("THE VALUE 2");
        expect3 = bsStatic("THE VALUE 3");
    }
    static int traverse_good_cb(BSTreeNode* node)
    {
        debug("KEY: %s", bdata((bstring) node->key));
        traverse_called++;
        return 0;
    }

    static int traverse_fail_cb(BSTreeNode* node)
    {
        debug("KEY: %s", bdata((bstring) node->key));
        traverse_called++;

        if(traverse_called == 2) {
            return 1;
        } else {
            return 0;
        }
    }
    BSTree* map = nullptr;
    static int traverse_called;
    static struct tagbstring test1,test2, test3,
                   expect1, expect2, expect3;
};

int BSTreeTest::traverse_called;
struct tagbstring BSTreeTest::test1, BSTreeTest::test2, BSTreeTest::test3,
        BSTreeTest::expect1, BSTreeTest::expect2, BSTreeTest::expect3;

void BSTreeTest::SetUp()
{
    map = BSTree_create(NULL);
    ASSERT_NE(map, nullptr);
}

void BSTreeTest::TearDown()
{
    BSTree_destroy(map);
}

using LcthwBSTreeTest = BSTreeTest;

TEST_F(LcthwBSTreeTest, OperationsTest)
{
    int rc = BSTree_set(map, &test1, &expect1);
    ASSERT_EQ(rc, 0);
    bstring result = static_cast<bstring>(BSTree_get(map, &test1));
    ASSERT_EQ(result, &expect1);

    rc = BSTree_set(map, &test2, &expect2);
    ASSERT_EQ(rc, 0);
    result = static_cast<bstring>(BSTree_get(map, &test2));
    ASSERT_EQ(result, &expect2);

    rc = BSTree_set(map, &test3, &expect3);
    ASSERT_EQ(rc, 0);
    result = static_cast<bstring>(BSTree_get(map, &test3));
    ASSERT_EQ(result, &expect3);

    rc = BSTree_traverse(map, traverse_good_cb);
    ASSERT_EQ(rc, 0);
    ASSERT_EQ(traverse_called, 3);

    traverse_called = 0;
    rc = BSTree_traverse(map, traverse_fail_cb);
    ASSERT_EQ(rc, 1);
    ASSERT_EQ(traverse_called, 2);

    bstring deleted = static_cast<bstring>(BSTree_delete(map, &test1));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect1);
    result = static_cast<bstring>(BSTree_get(map, &test1));
    ASSERT_EQ(result, nullptr);
    deleted = static_cast<bstring>(BSTree_delete(map, &test1));
    ASSERT_EQ(deleted, nullptr);

    deleted = static_cast<bstring>(BSTree_delete(map, &test2));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect2);
    result = static_cast<bstring>(BSTree_get(map, &test2));
    ASSERT_EQ(result, nullptr);
    deleted = static_cast<bstring>(BSTree_delete(map, &test2));
    ASSERT_EQ(deleted, nullptr);

    deleted = static_cast<bstring>(BSTree_delete(map, &test3));
    ASSERT_NE(deleted, nullptr);
    ASSERT_EQ(deleted, &expect3);
    result = static_cast<bstring>(BSTree_get(map, &test3));
    ASSERT_EQ(result, nullptr);
    deleted = static_cast<bstring>(BSTree_delete(map, &test3));
    ASSERT_EQ(deleted, nullptr);
}

TEST_F(LcthwBSTreeTest, fuzzingTest)
{
    BSTree* store = BSTree_create(nullptr);
    bstring numbers[100] = {nullptr};
    bstring data[100] = {nullptr};

    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i = 0; i < 100; i++)
    {
        int num = rand();
        numbers[i] = bformat("%d", num);
        data[i] = bformat("data %d", num);
        BSTree_set(store, numbers[i], data[i]);
    }

    for(int i = 0; i < 100; i++) {
        bstring value = static_cast<bstring>(BSTree_delete(store, numbers[i]));
        ASSERT_EQ(value, data[i]);
        ASSERT_EQ(BSTree_delete(store, numbers[i]), nullptr);

        for(int j = i+1; j < 99-i; j++) {
            bstring value = static_cast<bstring>(BSTree_get(store, numbers[j]));
            ASSERT_EQ(value, data[j]) << i << " " << j;
        }

        bdestroy(value);
        bdestroy(numbers[i]);
    }

    BSTree_destroy(store);
}

class StackTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    Stack *stack;
};

void StackTest::SetUp()
{
    stack = Stack_create();
    ASSERT_NE(stack, nullptr);
}

void StackTest::TearDown()
{
    Stack_destroy(stack);
}

using LcthwStackTest = StackTest;

TEST_F(LcthwStackTest, pushPopTest)
{
    constexpr int NUM_TESTS = 3;
    const char* tests[] = {"test1 data", "test2 data", "test3 data"};

    for(int i = 0; i < NUM_TESTS; i++)
    {
        Stack_push(stack, tests[i]);
        ASSERT_EQ(Stack_peek(stack), tests[i]);
    }

    ASSERT_EQ(Stack_count(stack), NUM_TESTS);

    for(int i = NUM_TESTS - 1; i >=0; i--) {
        auto val = static_cast<const char *>(Stack_pop(stack));
        ASSERT_EQ(val,tests[i]);
    }

    ASSERT_EQ(Stack_count(stack), 0);
}

class QueueTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    Queue *queue;
};

void QueueTest::SetUp()
{
    queue = Queue_create();
    ASSERT_NE(queue, nullptr);
}

void QueueTest::TearDown()
{
    Queue_destroy(queue);
}

using LcthwQueueTest = QueueTest;

TEST_F(LcthwQueueTest, enqueueDequeueTest)
{
    constexpr int NUM_TESTS = 3;
    const char* tests[] = {"test1 data", "test2 data", "test3 data"};

    for(int i = 0; i < NUM_TESTS; i++)
    {
        Queue_enqueue(queue, tests[i]);
        ASSERT_EQ(Queue_peek(queue), tests[0]);
    }

    ASSERT_EQ(Queue_count(queue), NUM_TESTS);

    for(int i = 0; i < NUM_TESTS; i++) {
        auto val = static_cast<const char *>(Queue_dequeue(queue));
        ASSERT_EQ(val,tests[i]);
    }

    ASSERT_EQ(Queue_count(queue), 0);
}

TEST_F(LcthwTest, ex43)
{
    constexpr int NUM_SAMPLES = 10;
    double samples[] = {
        6.1061334,
        9.6783204,
        1.2747090,
        8.2395131,
        0.3333483,
        6.9755066,
        1.0626275,
        7.6587523,
        4.9382973,
        9.5788115
    };

    Stats expect{ 55.84602, 425.1641, 10, 0.333, 9.678 };

    double expect_mean = 5.584602;
    double expect_stddev = 3.547868;

    auto Eq = [](double x, double y, double n)
    {
        return round(x * pow(10, n)) == round(y * pow(10, n));
    };

    Stats *st = Stats_create();
    ASSERT_NE(st, nullptr);

    for(int i = 0; i < NUM_SAMPLES; i++){
        Stats_sample(st, samples[i]);
    }

    Stats_dump(st);

    EXPECT_TRUE(Eq(st->sumsq, expect.sumsq, 3));
    EXPECT_TRUE(Eq(st->sum, expect.sum, 3));
    EXPECT_TRUE(Eq(st->min, expect.min, 3));
    EXPECT_TRUE(Eq(st->max, expect.max, 3));
    EXPECT_TRUE(Eq(st->n, expect.n, 3));
    EXPECT_TRUE(Eq(Stats_mean(st), expect_mean, 3));
    EXPECT_TRUE(Eq(Stats_stddev(st), expect_stddev, 3));

    Stats* st2 = Stats_recreate(expect.sum, expect.sumsq, expect.n,
                               expect.min, expect.max);

    EXPECT_EQ(st2->sum, expect.sum);
    EXPECT_EQ(st2->sumsq, expect.sumsq);
    EXPECT_EQ(st2->n, expect.n);
    EXPECT_EQ(st2->min, expect.min);
    EXPECT_EQ(st2->max, expect.max);
    EXPECT_TRUE(Eq(Stats_mean(st2), expect_mean, 3));
    EXPECT_TRUE(Eq(Stats_stddev(st2), expect_stddev, 3));
}

class RingBufferTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    RingBuffer *ringbuffer;
    static constexpr int length = 256;
};

void RingBufferTest::SetUp()
{
    ringbuffer = RingBuffer_create(length);
    ASSERT_NE(ringbuffer, nullptr);
}

void RingBufferTest::TearDown()
{
    RingBuffer_destroy(ringbuffer);
}

using LcthwRingBufferTest = RingBufferTest;

TEST_F(LcthwRingBufferTest, writeReadTest)
{
    constexpr int NUM_TESTS = 3;
    const char* tests[] = {"test1 data", "test2 data", "test3 data"};
    std::vector<int> lengths;
    for(int i = 0; i < 3; i++)
        lengths.push_back((int) strlen(tests[i]) + 1);
    for(size_t i = 0; i < NUM_TESTS; i++)
    {
        auto length = RingBuffer_write(ringbuffer,
                                       (char *) tests[i],
                                       lengths[i]);
        ASSERT_EQ(length, lengths[i]);
    }

    for(int i = 0; i < NUM_TESTS; i++) {
        char target[255];
        auto length = RingBuffer_read(ringbuffer, target, lengths[i]);
        ASSERT_TRUE(strcmp(tests[i], target) == 0);
    }
}








