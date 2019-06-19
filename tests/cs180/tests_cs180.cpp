#include <sstream>

#include "cs180.h"
#include "gtest/gtest.h"

TEST(cs180, stableMatchingBasic)
{
    std::stringstream in, out;

    in << "2 m1 m2 w1 w2 m1 w2 w1 m2 w1 w2 w1 m1 m2 w2 m1 m2\0";
    std::string s("w1 m2\n"
		  "w2 m1\n");
    cs180::StableMatching sm(in);
    sm(out);
    EXPECT_EQ(s, out.str());
}

TEST(cs180, stableMatchingBasicReversed)
{
    std::stringstream in, out;

    in << "2 m1 m2 w1 w2 m1 w2 w1 m2 w1 w2 w1 m1 m2 w2 m1 m2\0";
    std::string s("m1 w2\n"
		  "m2 w1\n");
    cs180::StableMatching sm(in);
    sm(out, false);
    EXPECT_EQ(s, out.str());
}

TEST(cs180, stableMatchingComplex)
{
    std::stringstream in, out;

    in << "7 "
    "adam brian deb charlie ethan fred greg "
    "susan lucy felicity debra katie mary jenny "
    "adam jenny katie felicity debra mary susan lucy "
    "brian mary katie felicity jenny lucy debra susan "
    "charlie mary jenny lucy susan felicity katie debra "
    "deb debra mary jenny felicity katie susan lucy "
    "ethan debra mary lucy jenny katie susan felicity "
    "fred debra susan jenny katie lucy mary felicity "
    "greg lucy mary felicity katie jenny susan debra "
    "lucy adam greg fred deb charlie ethan brian "
    "susan adam greg deb brian fred ethan charlie "
    "felicity ethan fred deb greg charlie brian adam "
    "debra deb ethan charlie greg brian fred adam "
    "jenny adam fred ethan deb charlie greg brian "
    "katie charlie ethan fred greg brian deb adam "
    "mary fred charlie greg ethan brian deb adam ";

    std::string s("debra deb\nfelicity brian\njenny adam\nkatie ethan\nlucy "
		  "greg\nmary charlie\nsusan fred\n");
    cs180::StableMatching sm(in);
    sm(out);
    
    EXPECT_EQ(s, out.str());
}
