/*!
 * \file mazefactory.cpp
 * \brief definitions for mazefactory heirarchy
 * \author mayank bansal
 */
#ifndef _GOF_MAZEFACTORY_CPP_
#define _GOF_MAZEFACTORY_CPP_

#include <iostream>
#include <cstring>
#include "mazefactory.h"
#include "maze.h"

std::unique_ptr<Mazefactory> Mazefactory::_instance = nullptr;

std::unique_ptr<Mazefactory> Mazefactory::Instance()
{
    if(_instance == nullptr)
    {
        const char* mazestyle = getenv("MAZESTYLE");
        if(mazestyle == nullptr) mazestyle = "default";
        if(strcmp(mazestyle, "bombed") == 0)
            _instance = std::unique_ptr<BombedMazeFactory>(new BombedMazeFactory);
        else if(strcmp(mazestyle, "enchanted") == 0)
            _instance = std::unique_ptr<EnchantedMazefactory>(new EnchantedMazefactory);
        else
            _instance = std::unique_ptr<Mazefactory>(new Mazefactory);
    }
    return std::move(_instance);
}

/// \brief constructor for MazeFactory
Mazefactory::Mazefactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout<<"creating MazeFactory"<<std::endl;
#endif
}
Mazefactory::~Mazefactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout<<"destroying MazeFactory"<<std::endl;
#endif

}

/*! \brief make a maze
 *
 * \return unique pointer to a maze
 */
std::unique_ptr<Maze> Mazefactory::MakeMaze() const
{
    return std::make_unique<Maze>();
}

/*! \brief make a room 
 *
 * \return unique pointer to a room
 */
std::unique_ptr<Room> Mazefactory::MakeRoom(int rn) const
{
    return std::make_unique<Room>(rn);
}

/*!
 * \brief Make a Door
 *
 * \param r1
 * \param r2
 *
 * \return door
 */
std::unique_ptr<Door> Mazefactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    return std::make_unique<Door>(r1, r2);
}

/*!
 * \brief Make a Wall
 *
 * \return
 */
std::unique_ptr<Wall> Mazefactory::MakeWall() const
{
    return std::make_unique<Wall>();
}
#endif /* ifndef _GOF_MAZEFACTORY_CPP_ */

/*! \brief Enchanted Maze factory constructor
 *
 *  creates maze components with a spell on them
 */
EnchantedMazefactory::EnchantedMazefactory()
    :Mazefactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "creating enchanted maze factory" << std::endl; 
#endif
}

/*! \brief Enchanted Maze factory destructor
 *
 *  destroys an enchanted maze factory
 */
EnchantedMazefactory::~EnchantedMazefactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "destroying enchanted maze factory" << std::endl;
#endif
}

/*! \brief MakeRoom
 *
 *  Make an enchanted room
 *
 * \param rn room number
 * \return unique ptr to room
 */
std::unique_ptr<Room> EnchantedMazefactory::MakeRoom(int rn) const
{
    return std::make_unique<EnchantedRoom>(rn, CastSpell());
}

/*! \brief Cast Spell
 *
 *  creates and returns a spell object
 *
 * \return spell unique pointer
 */
std::unique_ptr<Spell> EnchantedMazefactory::CastSpell() const
{
    return std::make_unique<Spell>("qwer","test");
}

/*! \brief Bombed Maze factory constructor
 *
 *  creates maze components with a spell on them
 */
BombedMazeFactory::BombedMazeFactory()
    :Mazefactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "creating bombed maze factory" << std::endl;
#endif
}

/*! \brief Bombed Maze factory destructor
 *
 *  destroys an Bombed maze factory
 */
BombedMazeFactory::~BombedMazeFactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "destroying Bombed maze factory" << std::endl;
#endif
}

/*!
 * \brief MakeRoom
 *
 * make a bombed room
 *
 * \param n room no
 *
 * \return reference to room
 */
std::unique_ptr<Room> BombedMazeFactory::MakeRoom(int n) const
{
    return std::make_unique<RoomWithABomb>(n, MakeBomb(n));
}

/*!
 * \brief MakeWall
 *
 * make a bombed wall
 *
 * \return reference to wall
 */
std::unique_ptr<Wall> BombedMazeFactory::MakeWall() const
{
    return std::make_unique<BombedWall>();
}

/*!
 * \brief MakeBomb
 *
 * make a bomb
 *
 * \return reference to bomb
 */
std::unique_ptr<Bomb> BombedMazeFactory::MakeBomb(int n) const
{
    return std::make_unique<Bomb>(n);
}

/*!
 * \brief MazePrototypeFactory::MazePrototypeFactory crate factory of prototypes
 * \param m
 * \param r
 * \param d
 * \param w
 */
MazePrototypeFactory::MazePrototypeFactory(std::unique_ptr<Maze> m, std::unique_ptr<Room> r,
                                           std::unique_ptr<Door> d, std::unique_ptr<Wall> w)
    : Mazefactory (),
      _prototypeMaze(std::move(m)),
      _prototypeRoom(std::move(r)),
      _prototypeDoor(std::move(d)),
      _prototypeWall(std::move(w))
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Creating maze prototype factory" << std::endl;
#endif
}

/*!
 * \brief MazePrototypeFactory::~MazePrototypeFactory destroy factory of prototypes
 */
MazePrototypeFactory::~MazePrototypeFactory()
{
#ifdef LOG_CONSTRUCTOR_DESTRUCTOR_CALLS
    std::cout << "Destroying maze prototype factory" << std::endl;
#endif
}

/*!
 * \brief MazePrototypeFactory::MakeMaze create a maze
 * \return
 */
std::unique_ptr<Maze> MazePrototypeFactory::MakeMaze() const
{
    return _prototypeMaze->Clone();
}

/*!
 * \brief MazePrototypeFactory::MakeRoom create a room
 * \param rno
 * \return
 */
std::unique_ptr<Room> MazePrototypeFactory::MakeRoom(int rno) const
{
    std::unique_ptr<Room> room = _prototypeRoom->Clone();
    room->Initialize(rno);
    return room;
}

/*!
 * \brief MazePrototypeFactory::MakeDoor create a door
 * \param r1
 * \param r2
 * \return
 */
std::unique_ptr<Door> MazePrototypeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    std::unique_ptr<Door> door = _prototypeDoor->Clone();
    door->Initialize(r1, r2);
    return door;
}

/*!
 * \brief MazePrototypeFactory::MakeWall
 * \return
 */
std::unique_ptr<Wall> MazePrototypeFactory::MakeWall() const
{
    return _prototypeWall->Clone();
}
