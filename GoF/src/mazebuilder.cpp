#include <iostream>

#include "dbg.h"
#include "mazebuilder.h"
#include "maze.h"

namespace gof {

MazeBuilder::MazeBuilder()
{
    debug("Creating Maze Builder");
}

MazeBuilder::~MazeBuilder()
{
    debug("Destroying Maze Builder");
}

StandardMazeBuilder::StandardMazeBuilder()
    :MazeBuilder (),
      _maze(nullptr)
{
    debug("Creating Standard Maze builder");
}

StandardMazeBuilder::~StandardMazeBuilder()
{
    debug("Destroying Standard Maze Builder");
}

void StandardMazeBuilder::BuildMaze()
{
    _maze = std::make_unique<Maze>();
}

std::unique_ptr<Maze> StandardMazeBuilder::GetMaze()
{
    return std::move(_maze);
}

void StandardMazeBuilder::BuildRoom(int rno)
{
    try {
        _maze->RoomNo(rno);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        auto r = std::make_shared<Room>(rno);
        _maze->AddRoom(r);
        auto w = std::make_shared<Wall>();
        r->SetSide(Direction::East, w);
        r->SetSide(Direction::West, w);
        r->SetSide(Direction::North, w);
        r->SetSide(Direction::South, w);
    }
}

void StandardMazeBuilder::BuildDoor(int r1, int r2)
{
    auto room1 = _maze->RoomNo(r1);
    auto room2 = _maze->RoomNo(r2);
    auto d = std::make_shared<Door>(room1, room2);
    room1->SetSide(CommonWall(room1, room2), d);
    room2->SetSide(CommonWall(room2, room1), d);
}

Direction StandardMazeBuilder::CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    if(r1->GetRoomNo() == 1) return Direction::East;
    else return Direction::West;
}

CountingMazeBuilder::CountingMazeBuilder()
    :_rooms(0),
      _doors(0)
{
    debug("Creating Counting Maze Builder");
}

CountingMazeBuilder::~CountingMazeBuilder()
{
    debug("Destroying Counting Maze Builder");
}

void CountingMazeBuilder::BuildMaze()
{
}

std::unique_ptr<Maze> CountingMazeBuilder::GetMaze()
{
    return nullptr;
}


void CountingMazeBuilder::BuildRoom(int rno)
{
    _rooms++;
}

void CountingMazeBuilder::BuildDoor(int r1, int r2)
{
    _doors++;
}

void CountingMazeBuilder::GetCounts(int& rooms, int& doors) const
{
    rooms = _rooms;
    doors = _doors;
}

}
