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


std::shared_ptr<MapSite> Room::GetSide(Direction d) const
{
    return _sides[static_cast<int>(d)];
}

int Room::GetRoomNo() const
{
    return _roomNumber;
}

void Room::SetSide(Direction d, std::shared_ptr<MapSite> ms)
{
    auto mapsite = dynamic_cast<Room *>(ms.get());
    if(mapsite == nullptr)
        _sides[static_cast<int>(d)] = ms;
    else throw std::invalid_argument("rooms cannot contain other rooms");
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

Door::Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
    :_room1(r1),
     _room2(r2),
     _isOpen(true)
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    std::cout << "Creating Door " << tr1->GetRoomNo() << " "
              << tr2->GetRoomNo() << std::endl;
    else
        throw std::runtime_error("Door Constructor: Rooms do not exist!!");
#endif
}

Door::~Door()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    std::cout << "Destroying Door " << tr1->GetRoomNo() << " "
              << tr2->GetRoomNo() << std::endl;
    else
        std::cout << "Destroying Door" << std::endl;
#endif
}

std::shared_ptr<Room> Door::OtherSideFrom(std::shared_ptr<Room> r)
{
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    {
        if(r->GetRoomNo() == tr1->GetRoomNo())
            return tr1;
        else if(r->GetRoomNo() == tr2->GetRoomNo())
            return tr2;
    }
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

void Maze::AddRoom(std::shared_ptr<Room> r)
{
    auto rn = static_cast<std::vector<Room*>::size_type>(r->GetRoomNo());
    if(rn > 0 && _rooms.size() == rn-1)
        _rooms.push_back(r);
    else
        throw std::invalid_argument("MazeGame : Failed to add Room\n"
                                    "Room numbers should be added in increaing"
                                    " order of positive room numbers starting"
                                    " at Room no 1");
}

std::shared_ptr<Room> Maze::RoomNo(int rn) const
{
    auto rno = static_cast<std::vector<Room*>::size_type>(rn);
    if(rn > 0 && _rooms.size() >= rno)
        return _rooms[rno-1];
    else
        throw std::invalid_argument("Room numbers should be in valid range");
}

/*! \brief Spell constructor
 *
 *  create a spell object
 */
Spell::Spell(std::string q,std::string a)
    : q(q),
      a(a)
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "creating a spell!!" << std::endl;
#endif
}

/*! \brief Spell destructor
 *
 *  destroys a spell object
 */
Spell::~Spell()
{
    #ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "destroy a spell" << std::endl;
    #endif
}

/*! \brief dispell this spell
 *
 *  if provided string is correct the spell is dispelled
 *
 * \param s answer string
 * \return true if s == answer
 *         false otherwise
 */
bool Spell::dispell(std::string s) {
    return s == this->a;
}
/*! \brief Enchanted room consructor *
 *  create an enchanted room.Enchanted rooms need a spell to be broken.
 *
 * \param n room number
 * \param s spell
 */
EnchantedRoom::EnchantedRoom(int n, std::unique_ptr<Spell> s)
    : Room(n),
      _spell(std::move(s))
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout<<"Creating enchanted room" << n << std::endl;
#endif
}

/*! \brief Enchanted Room destructor
 *
 *  destroys an enchanted room
 */
EnchantedRoom::~EnchantedRoom()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying enchanted Room" << this->GetRoomNo() << std::endl;
#endif
}

/*! \brief enter this room
 *
 *  currently tells if the spell answer is right or wrong.
 *  \todo on adding player class enter only if spell broken
 *
 */
void EnchantedRoom::enter() {
    if(_spell->dispell("test"))
        std::cout << "Spell broken!! location:" << this->GetRoomNo() << std::endl;
    else
        std::cout << "Spell not broken!! location:" << this->GetRoomNo() << std::endl;
}

/*!
 * \brief Bomb constructor
 *
 * \param n time bomb goes off
 */
Bomb::Bomb(int n)
    :_time(n)
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Bomb!! time:" << this->_time << std::endl;
#endif
}

/*!
 * \brief Bomb destructor
 */
Bomb::~Bomb()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Bomb!!" << std::endl;
#endif
}

/*!
 * \brief Get Detonation Time
 * \return detonation time
 */
int Bomb::GetDetonationTime()
{
    return _time;
}

/*!
 * \brief Create Room With A Bomb
 * \param n room no
 * \param b bomb
 */
RoomWithABomb::RoomWithABomb(int n, std::unique_ptr<Bomb> b)
    : Room(n),
      _bomb(std::move(b))
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating Room with a bomb!!" << this->GetRoomNo() << std::endl;
#endif
}

/*!
 * \brief Destroy Room With A Bomb
 */
RoomWithABomb::~RoomWithABomb()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying Room with a bomb!!" << std::endl;
#endif
}

/*!
 * \brief enter behaviour of bombed room
 */
void RoomWithABomb::enter()
{
    std::cout << "location : time" << this->GetRoomNo() <<" : " << _bomb->GetDetonationTime() << std::endl;
}

BombedWall::BombedWall()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating bombed Wall" << std::endl;
#endif
}

BombedWall::~BombedWall()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying bombed Wall" << std::endl;
#endif
}

void BombedWall::enter()
{
    std::cout << "!!you've hit a bombed wall!!" << std::endl;
}
