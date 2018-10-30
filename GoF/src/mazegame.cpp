/// \file mazegame.cpp
/// \brief implementation for MazeGme
///
/// implementation for a MazeGame that user can use to create a MazeGame.

/// \author Mayank Bansal

#include "mazegame.h"
#include "maze.h"
#include <iostream>

MazeGame::MazeGame()
    :_maze(nullptr)
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating MazeGame" << std::endl;
#endif
}

MazeGame::MazeGame(MazeGame&& rhs) = default;
MazeGame& MazeGame::operator=(MazeGame&& rhs) = default;

MazeGame::~MazeGame()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "destroying MazeGame" << std::endl;
#endif
}

/// \todo make it a unique pointer instead of simple pointer
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

void MazeGame::CreateMaze(std::shared_ptr<Mazefactory> mf)
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
}
