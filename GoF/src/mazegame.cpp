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

MazeGame::~MazeGame()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "destroying MazeGame" << std::endl;
#endif
}

MazeGame::MazeGame(MazeGame&& rhs) = default;

MazeGame& MazeGame::operator=(MazeGame&& rhs) = default;

MazeGame::MazeGame(const MazeGame& rhs)
    :_maze(std::make_unique<Maze>(*rhs._maze))
{}

MazeGame& MazeGame::operator=(const MazeGame& rhs)
{
    *_maze = *rhs._maze;
    return *this;
}

/// \todo make it a unique pointer instead of simple pointer
void MazeGame::CreateMaze()
{
    _maze = std::make_unique<Maze>();
    Room *r1, *r2;
    try {
        r1 = new Room(1);
        r2 = new Room(2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    Door* theDoor = new Door(r1, r2);

    _maze->AddRoom(r1);
    _maze->AddRoom(r2);

    r1->SetSide(Direction::North, new Wall);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, new Wall);
    r1->SetSide(Direction::West, new Wall);

    r2->SetSide(Direction::North, new Wall);
    r2->SetSide(Direction::East, new Wall);
    r2->SetSide(Direction::South, new Wall);
    r2->SetSide(Direction::West, theDoor);

}
