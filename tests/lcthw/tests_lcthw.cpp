#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "gtest/gtest.h"
#include "lcthw.h"
#include "ex17_ds.h"
#include "Fixture.h"


TEST(lcthw, ex1)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex1(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You are 100 miles away.\n");
    fclose(out_test);
}

TEST(lcthw, ex3)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex3(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "I am 23 years old.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "I am 74 inches tall.\n");
    fclose(out_test);
}

TEST(lcthw, ex7)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex7(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You are 100 miles away.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You have 2.345000 levels of power.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You have 56789.453200 awesome super powers.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "I have an initial A.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "I have a first name Zed.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "I have a last name Shaw.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "My whole name is Zed A Shaw.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You have 100 bugs at the imaginary rate of 1.200000.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "The entire universe has 1073741824 bugs.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You are expected to have 120.000000 bugs.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "That is only a 1.117587e-07 portion of the universe.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf,  "Which means you should care 0%.\n");
    fclose(out_test);
}

TEST(lcthw, ex8NoArg)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 1;
    char *argv[] = {"test"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You only have one argument. You suck.\n");
    fclose(out_test);
}

TEST(lcthw, ex8Arg)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 2;
    char *argv[] = {"test", "here it is"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Here's your arguments:\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "test here it is ");
    fclose(out_test);
}

TEST(lcthw, ex8TooManyArgs)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 4;
    char *argv[] = {"test", "here it is", "tease", "fried"};
    int a = ex8(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "You have too many arguments. You suck.\n");
    fclose(out_test);
}

TEST(lcthw, ex9)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex9(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 \n");
    fclose(out_test);
}

TEST(lcthw, ex10NoArgs)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 1;
    char *argv[] = {"test"};
    int a = ex10(argc, argv, out_test);
    EXPECT_EQ(a, 1);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "ERROR: You need one argument.\n" );
    fclose(out_test);
}

TEST(lcthw, ex10Args)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 2;
    char *argv[] = {"test", "uyYaieyobDOYEIAU"};
    int a = ex10(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "0: 'U'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "3: 'A'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "4: 'I'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "5: 'E'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "6: 'Y'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "7: 'O'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "8: b is not a vowel\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "9: D is not a vowel\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "10: 'O'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "11: 'Y'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "12: 'E'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "13: 'I'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "14: 'A'\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "15: 'U'\n" );
    fclose(out_test);
}

TEST(lcthw, ex11)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex11(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "numbers: 0 0 0 0\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name each: 97 0 0 0\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name each: y Z D a\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name each: \xFF \xFF \xFF \xFF\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name: a\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "numbers: 1 2 3 4\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name each: Z e d " );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name: Zed\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "another: Zed\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "another each: Z e d " );
    fclose(out_test);
}

TEST(lcthw, ex12)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex12(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255], buf2[255];
    fgets(buf, 255, out_test);
    sprintf(buf2, "The size of an int: %u\n", sizeof(int));
    EXPECT_STREQ(buf, buf2);
    fgets(buf, 255, out_test);
    sprintf(buf2, "The size of areas (int[]): %u\n", sizeof(int)*5);
    EXPECT_STREQ(buf, buf2);
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "The number of ints in areas: 5\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "The first area is 10, the 2nd 12.\n" );
    fgets(buf, 255, out_test);
    sprintf(buf2, "The size of a char: %u\n", sizeof(char));
    EXPECT_STREQ(buf, buf2 );
    fgets(buf, 255, out_test);
    sprintf(buf2, "The size of name (char[]): %u\n", sizeof(char)*4);
    EXPECT_STREQ(buf, buf2);
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "The number of chars: 4\n" );
    fgets(buf, 255, out_test);
    sprintf(buf2,"The size of full_name (char[]): %u\n", sizeof(char)*12);
    EXPECT_STREQ(buf, buf2 );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "The number of chars: 12\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "name=\"Zed\" and full_name=\"Zed A. Shaw\"\n" );
    fclose(out_test);
}

TEST(lcthw, ex13)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 3;
    char *argv[] = {"test", "hey", "there"};
    int a = ex13(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "arg 1: hey\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "arg 2: there\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "state 0: California\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "state 1: Oregon\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "state 2: Washington\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "state 3: Texas\n" );
    fclose(out_test);
}

TEST(lcthw, ex14)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int argc = 3;
    char *argv[] = {"test", "bruce wills", "bruce123 wills#%!"};
    int a = ex14(argc, argv, out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "test\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "bruce wills\n" );
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "bruce wills\n" );
}

TEST(lcthw, ex15)
{
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    int a = ex15(out_test);
    EXPECT_EQ(a, 0);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "---\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "---\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "---\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Alan has 23 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Frank has 43 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Mary has 12 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "John has 89 years alive.\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Lisa has 2 years alive.\n");
    fgets(buf, 255, out_test);
    fclose(out_test);
}

TEST(lcthw, ex16)
{
    struct Person* joe = CreatePerson("Joe Frank", 32, 64,140);
    EXPECT_NE(joe, nullptr);
    FILE* out_test = fopen("lcthw_gtest.txt", "w+");
    PrintPerson(out_test, joe);
    fseek(out_test, 0, SEEK_SET);
    char buf[255];
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Name : Joe Frank\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Age : 32\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Height : 64\n");
    fgets(buf, 255, out_test);
    EXPECT_STREQ(buf, "Weight : 140\n");
    DestroyPerson(&joe);
    EXPECT_EQ(joe, nullptr);
    fclose(out_test);
}

using LcthwEx17DeathTest = Fixture;
using LcthwEx17Test = Fixture;

TEST_F(LcthwEx17DeathTest, ex17InSufficientArguments)
{
    errno = 0;
    int argc = 2;
    const char *argv[] = {"ex17", "test_dbFile"};
    EXPECT_EXIT(ex17(argc, argv), ::testing::ExitedWithCode(1),
                "USAGE: dessPat <dbfile> <action> ");
}

#ifdef C_SERVICE_MOCK_TESTS
TEST_F(LcthwEx17DeathTest, ex17MallocFail1)
{
    EXPECT_CALL(*(Fixture::_libc), malloc(::testing::_))
                                       .WillRepeatedly(::testing::Return(nullptr));
    errno = ENOMEM;
    ::testing::Mock::AllowLeak((Fixture::_libc).get());
    int argc = 3;
    const char *argv[] = {"ex17", "test_dbFile", "c"};
    EXPECT_EXIT(ex17(argc, argv), ::testing::ExitedWithCode(1),
                "Cannot create Connection");
}
#endif // C_SERVICE_MOCK_TESTS

TEST_F(LcthwEx17DeathTest, ex17TryingToReadNonExistentDatabaseFile)
{
    errno = 0;
    int argc = 4;
    const char *argv[] = {"ex17", "test_gtsgserufldfjnaku", "g"};
    EXPECT_EXIT(ex17(argc, argv), ::testing::ExitedWithCode(1),
               "failed to open file");
}

TEST_F(LcthwEx17DeathTest, ex17InvalidRecordNumber)
{
    errno = 0;
    int argc = 4;
    auto s = std::to_string(MAX_ROWS);
    const char *argv[] = {"ex17", "test_dbFile", "c", s.c_str()};
    EXPECT_EXIT(ex17(argc, argv), ::testing::ExitedWithCode(1),
               "there are not that many records");
}

TEST_F(LcthwEx17DeathTest, databaseFileDoesNotExist)
{
    errno = 0;
    int argc = 4;
    const char *argv[] = {"ex17", "aslifghwgwhwgrwn", "g", "1"};
    EXPECT_EXIT(ex17(argc, argv), ::testing::ExitedWithCode(1),
               "failed to open file");
}


