/// \file maze.cpp
/// \brief contains implementations for map sites and maze used in a a maze game.
///
/// this file contains a class hierarchy for different MapSites used
/// in a MazeGame.
/// \author Mayank Bansal

#include <iostream>
#include <stdexcept>

#include "maze.h"

MapSite::~MapSite()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying MapSite" << std::endl;
#endif
}

Room::Room(int roomNo)
    :_roomNumber(roomNo),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Room " << _roomNumber << std::endl;
#endif
}

Room::~Room()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Room " << _roomNumber << std::endl;
#endif
}


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
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Wall" << std::endl;
#endif
}

Wall::~Wall()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Wall" << std::endl;
#endif
}

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
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Door " << _room1->GetRoomNo() << " "
              << _room2->GetRoomNo() << std::endl;
#endif
}

Door::~Door()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Door " << _room1->GetRoomNo() << " "
              << _room2->GetRoomNo() << std::endl;
#endif
}

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
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Maze" << std::endl;
#endif
}

Maze::~Maze()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Maze" << std::endl;
#endif
}

void Maze::AddRoom(Room* r)
{
    auto rn = static_cast<std::vector<Room*>::size_type>(r->GetRoomNo());
    if(rn > 0 && _rooms.size() == rn-1)
        _rooms.push_back(r);
    else
        throw std::invalid_argument("Room numbers should be added in increaing"
                                    " order of positive room numbers starting"
                                    " at Room no 1");
}

Room* Maze::RoomNo(int rn) const
{
    auto rno = static_cast<std::vector<Room*>::size_type>(rn);
    if(rn > 0 && _rooms.size() >= rno)
        return _rooms[rno];
    else
        throw std::invalid_argument("Room numbers should be in valid range");
}
