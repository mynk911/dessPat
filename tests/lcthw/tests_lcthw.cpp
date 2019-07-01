#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "gtest/gtest.h"

#include "dessPatConfig.h"
#include "dbg.h"

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
