/*!
 * \file mazefactory.cpp
 * \brief definitions for mazefactory heirarchy
 * \author mayank bansal
 */

#include <iostream>
#include <cstring>

#include "dbg.h"
#include "mazefactory.h"
#include "maze.h"

namespace gof {
namespace creational {

std::unique_ptr<MazeFactory> MazeFactory::_instance = nullptr;


/** @Brief manages the single instance of MazeFactory.
 *
 * creates a mazefactory instance on first call. The type of object
 * can be changed using environment variable MAZESTYLE. Subsequent calls 
 * return the same object.
 *
 * @return <b>{nil}</b> pointer to MazeFactory.
 */
MazeFactory* MazeFactory::Instance()
{
    if(_instance == nullptr)
    {
        const char* mazestyle = getenv("MAZESTYLE");
        if(mazestyle == nullptr) mazestyle = "default";
        if(strcmp(mazestyle, "bombed") == 0)
            _instance = std::unique_ptr<BombedMazeFactory>(new BombedMazeFactory);
        else if(strcmp(mazestyle, "enchanted") == 0)
            _instance = std::unique_ptr<EnchantedMazeFactory>(new EnchantedMazeFactory);
	// TODO : add MazePrototypeFactory case here.
        else
            _instance = std::unique_ptr<MazeFactory>(new MazeFactory);
    }
    return _instance.get();
}



/** @Brief MazeFactory constructor.
 */
MazeFactory::MazeFactory()
{
    debug("creating MazeFactory");
}


/** @Brief MazeFactory destructor.
 */
MazeFactory::~MazeFactory()
{
    debug("destroying MazeFactory");

}


/** @Brief Factory method for creating Maze.
 * @return an instance of Maze.
 */
std::unique_ptr<Maze> MazeFactory::MakeMaze() const
{
    return std::make_unique<Maze>();
}


/** @Brief Factory method for creating Room.
 * @param  rn  room number to assign to room.
 * @return <b>{std::unique_ptr<Door>}</b> an instance of room.
 */
std::unique_ptr<Room> MazeFactory::MakeRoom(int rn) const
{
    return std::make_unique<Room>(rn);
}


/** @Brief Factory method for creating Door.
 * @param r1 <b>{std::unique_ptr<Room>}</b> Room connected to this door.
 * @param std <b>{nil}</b> Room connected to this door.
 * @return <b>{std::unique_ptr<Door>}</b> an instance of door.
 */
std::unique_ptr<Door> MazeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    return std::make_unique<Door>(r1, r2);
}

/** @Brief Factory Method for creating Wall.
 * @return <b>{std::unique_ptr<Wall>}</b> an instance of type wall.
 */
std::unique_ptr<Wall> MazeFactory::MakeWall() const
{
    return std::make_unique<Wall>();
}

/// \brief Enchanted Maze factory constructor
///
///  creates maze components with a spell on them
EnchantedMazeFactory::EnchantedMazeFactory()
    :MazeFactory()
{
    debug("creating enchanted maze factory");
}

/// \brief Enchanted Maze factory destructor
///
/// destroys an enchanted maze factory
EnchantedMazeFactory::~EnchantedMazeFactory()
{
   debug("destroying enchanted maze factory");
}

/// \brief MakeRoom
///
/// Make an enchanted room
///
/// \param rn room number
/// \return unique ptr to room
std::unique_ptr<Room> EnchantedMazeFactory::MakeRoom(int rn) const
{
    return std::make_unique<EnchantedRoom>(rn, CastSpell());
}

/// \brief Cast Spell
///
/// creates and returns a spell object
///
/// \return spell unique pointer
std::unique_ptr<Spell> EnchantedMazeFactory::CastSpell() const
{
    return std::make_unique<Spell>("qwer","test");
}

/// \brief Bombed Maze factory constructor
///
/// creates maze components with a spell on them
BombedMazeFactory::BombedMazeFactory()
    :MazeFactory()
{
    debug("creating bombed maze factory");
}

/// \brief Bombed Maze factory destructor
///
/// destroys an Bombed maze factory
BombedMazeFactory::~BombedMazeFactory()
{
    debug("destroying Bombed maze factory");
}

/// \brief MakeRoom
///
/// make a bombed room
///
/// \param n room no
///
/// \return reference to room
std::unique_ptr<Room> BombedMazeFactory::MakeRoom(int n) const
{
    return std::make_unique<RoomWithABomb>(n, MakeBomb(n));
}

/// \brief MakeWall
///
/// make a bombed wall
///
/// \return reference to wall
std::unique_ptr<Wall> BombedMazeFactory::MakeWall() const
{
    return std::make_unique<BombedWall>();
}

/// \brief MakeBomb
///
/// make a bomb
///
/// \return reference to bomb
std::unique_ptr<Bomb> BombedMazeFactory::MakeBomb(int n) const
{
    return std::make_unique<Bomb>(n);
}

/// \brief MazePrototypeFactory::MazePrototypeFactory crate factory of prototypes
///
/// \param m
/// \param r
/// \param d
/// \param w
MazePrototypeFactory::MazePrototypeFactory(std::unique_ptr<Maze> m, std::unique_ptr<Room> r,
                                           std::unique_ptr<Door> d, std::unique_ptr<Wall> w)
    : MazeFactory (),
      _prototypeMaze(std::move(m)),
      _prototypeRoom(std::move(r)),
      _prototypeDoor(std::move(d)),
      _prototypeWall(std::move(w))
{
    debug("Creating maze prototype factory");
}

/// \brief MazePrototypeFactory::~MazePrototypeFactory destroy factory of prototypes
MazePrototypeFactory::~MazePrototypeFactory()
{
    debug("Destroying maze prototype factory");
}

/// \brief MazePrototypeFactory::MakeMaze create a maze
///
/// \return pointer to maze
std::unique_ptr<Maze> MazePrototypeFactory::MakeMaze() const
{
    return _prototypeMaze->Clone();
}

/// \brief MazePrototypeFactory::MakeRoom create a room
///
/// \param rno
///
/// \return pointer to room
std::unique_ptr<Room> MazePrototypeFactory::MakeRoom(int rno) const
{
    std::unique_ptr<Room> room = _prototypeRoom->Clone();
    room->Initialize(rno);
    return room;
}

/// \brief MazePrototypeFactory::MakeDoor create a door
///
/// \param r1
/// \param r2
///
/// \return pointer to door
std::unique_ptr<Door> MazePrototypeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    std::unique_ptr<Door> door = _prototypeDoor->Clone();
    door->Initialize(r1, r2);
    return door;
}

/// \brief MazePrototypeFactory::MakeWall
///
/// \return pointer to wall.
std::unique_ptr<Wall> MazePrototypeFactory::MakeWall() const
{
    return _prototypeWall->Clone();
}

}}
