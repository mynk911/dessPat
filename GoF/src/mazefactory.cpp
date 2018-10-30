/*!
 * \file mazefactory.cpp
 * \brief definitions for mazefactory heirarchy
 * \author mayank bansal
 */
#ifndef _GOF_MAZEFACTORY_CPP_
#define _GOF_MAZEFACTORY_CPP_

#include <iostream>

#include "mazefactory.h"
#include "maze.h"

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


