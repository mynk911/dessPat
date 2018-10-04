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

    /*!
     * \brief MazeGame move constructor
     * \param rhs reference to mazegame object
     */
    MazeGame(MazeGame&& rhs);

    /*!
     * \brief move assignment operator
     * \param rhs reference to mazeegame object
     * \return MazeGame reference
     */
    MazeGame& operator=(MazeGame&& rhs);

    /*!
     * \brief MazeGame copy constructor
     * \param rhs reference to mazegame object
     */
    MazeGame(const MazeGame& rhs);

    /*!
     * \brief copy assignment operator
     * \param rhs refernce to mazegame object
     * \return reference to MazeGame object
     */
    MazeGame& operator=(const MazeGame& rhs);

    /*!
      \brief MazeGame Destructor
     */
    ~MazeGame();


    /**
     * \brief Creates a maze game
     */
    void CreateMaze();
private:
    /*!
     * \brief pointer to maze
     */
    std::unique_ptr<Maze> _maze;
};

#endif
