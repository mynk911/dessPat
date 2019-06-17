#include "gtest/gtest.h"

#include "mazefactory.h"
#include "mazegame.h"
#include "maze.h"

void testCommonWalls(gof::MazeGame& mg,
                    gof::MazeTestPlayer& mP,
                    std::string& w)
{
    mg.playGame(mP, gof::Direction::North);
    EXPECT_EQ(w, mP._status);
    mg.playGame(mP, gof::Direction::South);
    EXPECT_EQ(w, mP._status);
}
void testRoom1Walls(gof::MazeGame& mg,
                    gof::MazeTestPlayer& mP,
                    std::string& w)
{
    testCommonWalls(mg, mP, w);
    mg.playGame(mP, gof::Direction::West);
    EXPECT_EQ(w, mP._status);
}

void testRoom2Walls(gof::MazeGame& mg,
                    gof::MazeTestPlayer& mP,
                    std::string& w)
{
    testCommonWalls(mg, mP, w);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ(w, mP._status);
}

TEST(gofTests, ManualCreationTest)
{
    gof::MazeGame mg;
    mg.CreateMaze();
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("Room:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("Room:2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, MazeFactoryTest)
{
    gof::MazeGame mg;
    mg.CreateMaze(gof::MazeFactory::Instance());
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("Room:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("Room:2", mP._status);
    testRoom2Walls(mg, mP, s);
}
