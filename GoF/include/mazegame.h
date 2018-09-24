/**
  \file mazegame.h
  \brief header for MazeGme

  declarations for a MazeGame that user can use to create a MazeGame.

  \author Mayank Bansal
  */

#ifndef _GOF_MAZEGAME_H_
#define _GOF_MAZEGAME_H_

#include "gof_export.h"

/*!
 * \brief forward declaration of class Maze \link maze.h
 */
class Maze;

///
/// \brief The MazeGame class
/// this class can be used to create a Maze Game.
///
class GOF_EXPORT MazeGame
{
public:
    /**
     * \brief MazeGame Constructor
     */
    MazeGame();

    /**
     * \brief Creates a maze game
     */
    Maze* CreateMaze();
};

#endif
