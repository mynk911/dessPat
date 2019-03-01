/// \file mazegame.cpp
/// \brief implementation for MazeGme
///
/// implementation for a MazeGame that user can use to create a MazeGame.

/// \author Mayank Bansal

#include <iostream>

#include "dbg.h"
#include "maze.h"
#include "mazegame.h"
#include "mazefactory.h"
#include "mazebuilder.h"

namespace gof {
namespace creational {

MazeGame::MazeGame()
    :_maze(nullptr)
{
    debug("Creating MazeGame");
}

MazeGame::MazeGame(MazeGame&& rhs) = default;
MazeGame& MazeGame::operator=(MazeGame&& rhs) = default;

MazeGame::~MazeGame()
{
    debug("destroying MazeGame");
}

void MazeGame::CreateMaze()
{
    _maze = std::make_unique<Maze>();

    auto r1 = std::make_shared<Room>(1);
    auto r2 = std::make_shared<Room>(2);

    auto theDoor = std::make_shared<Door>(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    auto w = std::make_shared<Wall>();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);

}

void MazeGame::CreateMaze(Mazefactory* mf)
{
    _maze = mf->MakeMaze();
    std::shared_ptr<Room> r1 = mf->MakeRoom(1);
    std::shared_ptr<Room> r2 = mf->MakeRoom(2);

    std::shared_ptr<Door> theDoor = mf->MakeDoor(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    std::shared_ptr<Wall> w = mf->MakeWall();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);

    r2->enter();
}

void MazeGame::CreateMaze(std::shared_ptr<MazeBuilder> mb)
{
    mb->BuildMaze();
    mb->BuildRoom(1);
    mb->BuildRoom(2);
    mb->BuildDoor(1,2);

    _maze = mb->GetMaze();

    auto cmb = std::dynamic_pointer_cast<CountingMazeBuilder>(mb);
    if(cmb != nullptr)
    {
        int rooms = 0 , doors = 0;
        cmb->GetCounts(rooms, doors);
        std::cout << "room count" << rooms << "door count" << doors << std::endl;
    }
}

/*! \name Factory Methods
 * factory methods to create maze and it's components
 */
///\{
/*!
 * \brief MazeGame::MakeMaze create a maze
 * \return pointer to maze
 */
std::unique_ptr<Maze> MazeGame::MakeMaze() const
{
    return std::make_unique<Maze>();
}

/*!
 * \brief MazeGame::MakeRoom create a room
 * \param rno
 * \return pointer to room
 */
std::unique_ptr<Room> MazeGame::MakeRoom(int rno) const
{
    return std::make_unique<Room>(rno);
}

/*!
 * \brief MazeGame::MakeDoor create a door
 * \param r1
 * \param r2
 * \return pointer to door
 */
std::unique_ptr<Door> MazeGame::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    return std::make_unique<Door>(r1, r2);
}

/*!
 * \brief MazeGame::MakeWall create a wall
 * \return pointer to wall
 */
std::unique_ptr<Wall> MazeGame::MakeWall() const
{
    return std::make_unique<Wall>();
}
///\}

void MazeGame::CreateMazebyFactoryMethods()
{
    _maze = MakeMaze();

    std::shared_ptr<Room> r1 = MakeRoom(1);
    std::shared_ptr<Room> r2 = MakeRoom(2);

    std::shared_ptr<Door> theDoor = MakeDoor(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::shared_ptr<Wall> w = MakeWall();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);
}

BombedMazeGame::BombedMazeGame()
    : MazeGame ()
{
    debug("Creating Bombed Maze Game");
}

BombedMazeGame::~BombedMazeGame()
{
    debug("Destroying Bombed Maze Game");
}

std::unique_ptr<Room> BombedMazeGame::MakeRoom(int rno) const
{
    return std::make_unique<RoomWithABomb>(rno, std::make_unique<Bomb>(rno));
}
std::unique_ptr<Wall> BombedMazeGame::MakeWall() const
{
    return std::make_unique<BombedWall>();
}

EnchantedMazeGame::EnchantedMazeGame()
{
    debug("Creating Enchanted Maze Game");
}
EnchantedMazeGame::~EnchantedMazeGame()
{
    debug("Destroying Enchanted Maze Game");
}

std::unique_ptr<Room> EnchantedMazeGame::MakeRoom(int rno) const
{
    return std::make_unique<EnchantedRoom>(rno, CastSpell());
}

std::unique_ptr<Spell> EnchantedMazeGame::CastSpell() const
{
    return std::make_unique<Spell>("test","ans");
}

std::unique_ptr<MazePrototypeFactory> MazeGame::MakePrototypeFactory()
{
    auto maze = std::make_unique<Maze>();
    auto room = std::make_unique<Room>();
    auto door = std::make_unique<Door>();
    auto wall = std::make_unique<Wall>();
    return std::make_unique<MazePrototypeFactory>(std::move(maze),
                                                  std::move(room),
                                                  std::move(door),
                                                  std::move(wall));
}

}}
