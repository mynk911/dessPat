/// \file maze.cpp
/// \brief contains implementations for map sites and maze used in a a maze game.
///
/// this file contains a class hierarchy for different MapSites used
/// in a MazeGame.
/// \author Mayank Bansal

#include <iostream>
#include "maze.h"

MapSite::~MapSite()
{}

Room::Room(int roomNo)
    :_roomNumber(roomNo),
      _sides{nullptr,nullptr,nullptr,nullptr}
{}

MapSite* Room::GetSide(Direction d) const
{
    return _sides[static_cast<int>(d)];
}

int Room::GetRoomNo() const
{
    return _roomNumber;
}

void Room::SetSide(Direction d, MapSite* ms)
{
    _sides[static_cast<int>(d)] = ms;
}

///
/// for now the implementation simply prints _roomNumber as we are only interested
/// creation of mazes
/// \todo add player class and make enter take it as argument to change location
/// on entering room
///
void Room::enter()
{
    std::cout << "location :" << _roomNumber << std::endl;
}

Wall::Wall()
{}

///
/// for now the implementation simply prints message as we are only interested
/// creation of mazes
/// \todo add player class and make enter take it as argument
///
void Wall::enter()
{
    std::cout << "!!you've hit a wall!!" << std::endl;
}

Door::Door(Room *r1, Room *r2)
    :_room1(r1),
     _room2(r2),
     _isOpen(true)
{}

Room* Door::OtherSideFrom(Room* r)
{
    if(r->GetRoomNo() == _room1->GetRoomNo())
        return _room2;
    else if(r->GetRoomNo() == _room2->GetRoomNo())
        return _room1;
    return nullptr;
}

///
/// for now the implementation simply prints message as we are only interested
/// creation of mazes
/// \todo add player class and make enter take it as argument, need to change
/// location according to current room user is in.
///
void Door::enter()
{
    if(_isOpen)
        std::cout<< "location changed";
    else
        std::cout<< "door is locked";
}

Maze::Maze()
{}

Maze::~Maze()
{}

void Maze::AddRoom(Room* r)
{
    auto rn = static_cast<std::vector<Room*>::size_type>(r->GetRoomNo());
    if(_maze.size() < rn)
        _maze.reserve(rn);
    _maze[rn] = r;
}

Room* Maze::RoomNo(int rn) const
{
    return _maze[static_cast<std::vector<Room*>::size_type>(rn)];
}
