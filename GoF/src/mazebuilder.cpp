/*!
 * \file mazebuilder.cpp
 *
 * maze builder classes implementations
 *
 * \author Mayank Bansal
 */

#include <iostream>

#include "dbg.h"
#include "mazebuilder.h"
#include "maze.h"

namespace gof {
namespace creational {

MazeBuilder::MazeBuilder()
{
    debug("Creating Maze Builder");
}

MazeBuilder::~MazeBuilder()
{
    debug("Destroying Maze Builder");
}

std::unique_ptr<Maze> MazeBuilder::GetMaze()
{
    return nullptr;
}

/*!
 * \brief StandardMazeBuilder constructor
 */
StandardMazeBuilder::StandardMazeBuilder()
    :MazeBuilder (),
      _maze(nullptr)
{
    debug("Creating Standard Maze builder");
}

/*!
 * \brief StandardMazeBuilder destructor
 */
StandardMazeBuilder::~StandardMazeBuilder()
{
    debug("Destroying Standard Maze Builder");
}

/*!
 * \brief Build Maze
 */
void StandardMazeBuilder::BuildMaze()
{
    _maze = std::make_unique<Maze>();
}

/*!
 * \brief Get Maze
 * \return reference to Maze
 */
std::unique_ptr<Maze> StandardMazeBuilder::GetMaze()
{
    return std::move(_maze);
}

/*!
 * \brief Build a Room
 * \param rno
 */
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

/*!
 * \brief Build a Door
 * \param r1
 * \param r2
 */
void StandardMazeBuilder::BuildDoor(int r1, int r2)
{
    auto room1 = _maze->RoomNo(r1);
    auto room2 = _maze->RoomNo(r2);
    auto d = std::make_shared<Door>(room1, room2);
    room1->SetSide(CommonWall(room1, room2), d);
    room2->SetSide(CommonWall(room2, room1), d);
}

/*!
 * \brief Find Common Wall
 * a very trivial implementation.
 *
 * \param r1
 * \param r2
 *
 * \return common wall's direction for each room
 */
Direction StandardMazeBuilder::CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    if(r1->GetRoomNo() == 1) return Direction::East;
    else return Direction::West;
}

/*!
 * \brief CountingMazeBuilder constructor
 */
CountingMazeBuilder::CountingMazeBuilder()
    :_rooms(0),
      _doors(0)
{
    debug("Creating Counting Maze Builder");
}

/*!
 * \brief CountingMazeBuilder Destructor
 */
CountingMazeBuilder::~CountingMazeBuilder()
{
    debug("Destroying Counting Maze Builder");
}

/*!
 * \brief CountingMazeBuilder::BuildRoom count rooms
 * \param rno
 */
void CountingMazeBuilder::BuildRoom(int rno)
{
    _rooms++;
}

/*!
 * \brief CountingMazeBuilder::BuildDoor count doors
 * \param r1
 * \param r2
 */
void CountingMazeBuilder::BuildDoor(int r1, int r2)
{
    _doors++;
}

void CountingMazeBuilder::GetCounts(int& rooms, int& doors) const
{
    rooms = _rooms;
    doors = _doors;
}

}}
