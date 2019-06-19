#include "cstdlib"

#include "gtest/gtest.h"
#include "mazefactory.h"
#include "mazebuilder.h"
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

class TestMazeFactory final : public gof::MazeFactory {
public:
    void destroySingleton()
    {
        this->~TestMazeFactory();
    }
};

TEST(gofTests, MazeFactoryTest)
{
    auto tmf = static_cast<TestMazeFactory*>
                    (operator new(sizeof(TestMazeFactory)));
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
    tmf->destroySingleton();
    operator delete (tmf);
    tmf = nullptr;
}

TEST(gofTests, EnchantedMazeFactoryTest)
{
    auto tmf = static_cast<TestMazeFactory*>
                    (operator new(sizeof(TestMazeFactory)));    
    putenv("MAZESTYLE=enchanted");
    gof::MazeGame mg;
    mg.CreateMaze(gof::MazeFactory::Instance());
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("EnchantedRoom:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("EnchantedRoom:2", mP._status);
    testRoom2Walls(mg, mP, s);
    tmf->destroySingleton();
    operator delete (tmf);
    tmf = nullptr;
}

TEST(gofTests, BombedMazeFactoryTest)
{    
    putenv("MAZESTYLE=bombed");
    gof::MazeGame mg;
    mg.CreateMaze(gof::MazeFactory::Instance());
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("BombedRoom:1 detonation 1", mP._status);
    std::string s = "BombedWall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("BombedRoom:2 detonation 2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, StandardMazeBuilderTesst)
{
    gof::MazeGame mg;
    std::stringstream out;
    mg.CreateMaze(out, std::make_shared<gof::StandardMazeBuilder>());
    EXPECT_EQ("", out.str());
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("Room:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("Room:2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, CountingMazeBuilderTesst)
{
    gof::MazeGame mg;
    std::stringstream out;
    mg.CreateMaze(out, std::make_shared<gof::CountingMazeBuilder>());
    EXPECT_EQ("room count 2 door count 1", out.str());
}

TEST(gofTests, FactoryMethodTest1)
{
    gof::MazeGame mg;
    mg.CreateMazebyFactoryMethods();
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("Room:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("Room:2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, FactoryMethodTest2)
{
    gof::EnchantedMazeGame mg;
    mg.CreateMazebyFactoryMethods();
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("EnchantedRoom:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("EnchantedRoom:2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, FactoryMethodTest3)
{
    gof::BombedMazeGame mg;
    mg.CreateMazebyFactoryMethods();
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("BombedRoom:1 detonation 1", mP._status);
    std::string s = "BombedWall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("BombedRoom:2 detonation 2", mP._status);
    testRoom2Walls(mg, mP, s);
}

TEST(gofTests, PrototypeFactoryTest)
{
    gof::MazeGame mg;
    gof::MazePrototypeFactory mf(std::make_unique<gof::Maze>(),
                              std::make_unique<gof::Room>(0),
                              std::make_unique<gof::Door>(),
                              std::make_unique<gof::Wall>());
    mg.CreateMaze(&mf);
    gof::MazeTestPlayer mP;
    mg.initGame(mP);
    EXPECT_EQ("Room:1", mP._status);
    std::string s = "Wall";
    testRoom1Walls(mg, mP, s);
    mg.playGame(mP, gof::Direction::East);
    EXPECT_EQ("Room:2", mP._status);
    testRoom2Walls(mg, mP, s);
}
