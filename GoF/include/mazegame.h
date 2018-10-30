/**
  \file mazegame.h
  \brief header for MazeGme

  declarations for a MazeGame that user can use to create a MazeGame.

  \author Mayank Bansal
  */

#ifndef _GOF_MAZEGAME_H_
#define _GOF_MAZEGAME_H_

#include <memory>
#include "gof_export.h"

#include "mazefactory.h"

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

    MazeGame(MazeGame&& rhs);
    MazeGame& operator=(MazeGame&& rhs);
    MazeGame(const MazeGame& rhs) = delete;
    MazeGame& operator=(const MazeGame& rhs) = delete;

    /*!
      \brief MazeGame Destructor
     */
    ~MazeGame();


    /**
     * \brief Creates a maze game
     */
    void CreateMaze();
    void CreateMaze(std::shared_ptr<Mazefactory> mf);
private:
    /*!
     * \brief pointer to maze
     */
    std::unique_ptr<Maze> _maze;
};

#endif
