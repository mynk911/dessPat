/// \file maze.cpp
/// \brief contains implementations for map sites and maze used in a a maze
//  game.
///
/// this file contains a class hierarchy for different MapSites used
/// in a MazeGame.
/// \author Mayank Bansal

#include <iostream>
#include <stdexcept>

#include "maze.h"
#include "dbg.h"

namespace gof {
namespace creational {

MapSite::MapSite()
{
    debug("Creating Mapsite");
}

MapSite::MapSite(MapSite&& other)
{
    debug("Creating MapSite : move");
}

MapSite& MapSite::operator=(MapSite&& other)
{
    debug("assigning MapSite : move");
    return *this;
}

MapSite::MapSite(const MapSite& other)
{
    debug("Creating MapSite : copy");
}

MapSite& MapSite::operator=(const MapSite& other)
{
    debug("assigning MapSite : copy");
    return *this;
}

MapSite::~MapSite()
{
    debug("Destroying MapSite");
}

Room::Room(int roomNo)
    :_roomNumber(roomNo),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("Creating Room ");
}

Room::Room()
    :_roomNumber(0),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("default Creating Room ");
}

Room::Room(Room&& other)
    :MapSite (std::move(other)),
      _roomNumber(std::move(other._roomNumber)),
      _sides(std::move(other._sides))
{
    debug("Creating Room : move");
}

Room& Room::operator=(Room&& other)
{
    MapSite::operator=(std::move(other));
    _roomNumber = std::move(other._roomNumber);
    _sides = std::move(other._sides);
    debug("assigning Room : move");
    return *this;
}

Room::Room(const Room& other)
    :MapSite (other),
      _roomNumber(other._roomNumber),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("Creating Room : copy");
}

Room& Room::operator=(const Room& other)
{
    MapSite::operator=(other);
    _roomNumber = other._roomNumber;
    _sides = {nullptr,nullptr,nullptr,nullptr};
    debug("assigning Room : copy");
    return *this;
}

Room::~Room()
{
    debug("Destroying Room ");
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

std::unique_ptr<Room> Room::Clone() const
{
    return std::make_unique<Room>(*this);
}

void Room::Initialize(int rno)
{
    _roomNumber = rno;
}

///
/// for now the implementation simply prints _roomNumber as we are only
//  interested in creation of mazes
/// \todo add player class and make enter take it as argument to change location
/// on entering room
///
void Room::enter()
{
    std::cout << "location :" << _roomNumber << std::endl;
}

Wall::Wall()
{
    debug("Creating Wall");
}

Wall::Wall(Wall&& other)
    :MapSite (std::move(other))
{
    debug("Creating Wall : move");
}

Wall& Wall::operator=(Wall&& other)
{
    MapSite::operator=(std::move(other));
    debug("assigning Wall : move");
    return *this;
}

Wall::Wall(const Wall& other)
    :MapSite (std::move(other))
{
    debug("Creating Wall : copy");
}

Wall& Wall::operator=(const Wall& other)
{
    MapSite::operator=(other);
    debug("assigning Wall : copy");
    return *this;
}

Wall::~Wall()
{
    debug("Destroying Wall");
}

std::unique_ptr<Wall> Wall::Clone() const
{
    return std::make_unique<Wall>(*this);
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
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
        debug("Creating Door %d %d", tr1->GetRoomNo(), tr2->GetRoomNo());
    else
        throw std::runtime_error("Door Constructor: Rooms do not exist!!");
}
Door::Door()
    :_room1(std::weak_ptr<Room>()),
      _room2(std::weak_ptr<Room>()),
      _isOpen(false)
{
    debug("Creating Door!!");
}


Door::Door(Door&& other)
    :MapSite (std::move(other)),
      _room1(std::move(other._room1)),
    _room2(std::move(other._room2))
{
    debug("Creating door : move");
}

Door& Door::operator=(Door&& other)
{
    MapSite::operator=(std::move(other));
    _room1 = std::move(other._room1);
    _room2 = std::move(other._room2);
    debug("assigning Wall : move");
    return *this;
}

Door::Door(const Door& other)
    :MapSite (other),
      _room1(std::weak_ptr<Room>()),
    _room2(std::weak_ptr<Room>())
{
    debug("Creating door : copy");
}

Door& Door::operator=(const Door& other)
{
    MapSite::operator=(other);
    _room1 = std::weak_ptr<Room>();
    _room2 = std::weak_ptr<Room>();
    debug("assigning door : copy");
    return *this;
}



std::unique_ptr<Door> Door::Clone() const
{
    return std::make_unique<Door>(*this);
}

void Door::Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    _room1 = r1;
    _room2 = r2;
}

Door::~Door()
{
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    debug("Destroying Door %d  %d", tr1->GetRoomNo(), tr2->GetRoomNo());
    else
    debug("Destroying Door");
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
    debug("Creating Maze");
}

Maze::Maze(Maze&& other)
    : _rooms(std::move(other._rooms))
{
    debug("Creating Maze : move");
}

Maze& Maze::operator=(Maze&& other)
{
    _rooms = std::move(other._rooms);
    debug("assigning Maze : move");
    return *this;
}

Maze::Maze(const Maze& other)
{
    debug("Creating Maze : copy");
}

Maze& Maze::operator=(const Maze& other)
{
    debug("assigning Maze : copy");
    return *this;
}

Maze::~Maze()
{
    debug("Destroying Maze");
}

std::unique_ptr<Maze> Maze::Clone() const
{
    return std::make_unique<Maze>(*this);
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
    debug("creating a spell!!");
}

/*! \brief Spell destructor
 *
 *  destroys a spell object
 */
Spell::~Spell()
{
    debug("destroy a spell");
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
    debug("Creating enchanted room");
}

/*! \brief Enchanted Room destructor
 *
 *  destroys an enchanted room
 */
EnchantedRoom::~EnchantedRoom()
{
    debug("Destroying enchanted Room %d", this->GetRoomNo());
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
    debug("Creating Bomb!! time: %d", this->_time);
}

/*!
 * \brief Bomb destructor
 */
Bomb::~Bomb()
{
    debug("Destroying Bomb!!");
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
    debug("Creating Room with a bomb!!, %d", this->GetRoomNo());
}

/*!
 * \brief Destroy Room With A Bomb
 */
RoomWithABomb::~RoomWithABomb()
{
    debug("Destroying Room with a bomb!!");
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
    debug("Creating bombed Wall");
}

BombedWall::~BombedWall()
{
    debug("Destroying bombed Wall");
}

void BombedWall::enter()
{
    std::cout << "!!you've hit a bombed wall!!" << std::endl;
}
}}
