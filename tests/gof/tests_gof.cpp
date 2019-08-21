#include "cstdlib"

#include "gtest/gtest.h"
#include "mazefactory.h"
#include "mazebuilder.h"
#include "mazegame.h"
#include "maze.h"
#include "shape.h"
#include "textview.h"
#include "textshape.h"
#include "composite.h"
#include "decorator.h"

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

// this class lets us access MazeFactory destructor so that we can delete
// the singleton.
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

// Here object of type EnchantedMazeFactory is deleted by ~MazeFactory which
// is non-virtual. This would not be a safe practice.
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

TEST(gofTests, ShapeTest)
{
    gof::Shape sp(2,4, 4,6);
    gof::Point p1(0,0), p2(0,0);
    
    sp.BoundingBox(&p1, &p2);
    EXPECT_EQ(p1.getX(), 2);
    EXPECT_EQ(p1.getY(), 4);
    EXPECT_EQ(p2.getX(), 4);
    EXPECT_EQ(p2.getY(), 6);
}

TEST(gofTests, TextViewTest)
{
    gof::TextView tv(2, 4, 2, 2);
    gof::Coord a,b,c,d;
    
    tv.GetOrigin(a, b);
    tv.GetExtent(c, d);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 4);
    EXPECT_EQ(c, 2);
    EXPECT_EQ(d, 2);
}

TEST(gofTests, TextShapeTest)
{
    gof::TextShape tsp(2,4, 4,6);
    gof::Point p1(0,0), p2(0,0);
    
    tsp.BoundingBox(&p1, &p2);
    EXPECT_EQ(p1.getX(), 2);
    EXPECT_EQ(p1.getY(), 4);
    EXPECT_EQ(p2.getX(), 4);
    EXPECT_EQ(p2.getY(), 6);
}

TEST(gofTests, Composite)
{
    auto cabinet = new gof::Cabinet("PC Cabinet");
    auto chassis = new gof::Chassis("PC Chassis");

    cabinet->Add(chassis);
    auto bus = new gof::Bus("MCA Bus");
    auto card = new gof::Card("16 Mbs Token Ring");
    bus->Add(card);
    chassis->Add(bus);
    auto fd = new gof::FloppyDisk("3.5in floppy");
    chassis->Add(fd);
    ASSERT_EQ(cabinet->NetPrice(), 37);
    delete fd; delete card; delete bus; delete chassis;
    delete cabinet;
}

TEST(gofTests, Decorator)
{
    auto window = new gof::Window();
    auto textView = new gof::TextV();
    auto sd = new gof::ScrollDecorator(textView);
    auto bd = new gof::BorderDecorator(sd,1);
    window->SetContents(bd);
    delete textView; delete sd; delete bd; delete window;
}
