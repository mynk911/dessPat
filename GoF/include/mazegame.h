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

namespace gof {
namespace creational {

/*!
 * \brief forward declaration of class Maze \link maze.h
 */
class Maze;
class Room;
class Door;
class Wall;
class Spell;
/*!
 * \brief forward declaration of class Maze \link mazebuilder.h
 */
class Mazefactory;
class MazeBuilder;
class MazePrototypeFactory;
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
    virtual ~MazeGame();

    virtual std::unique_ptr<Maze> MakeMaze() const;
    virtual std::unique_ptr<Room> MakeRoom(int rno) const;
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    virtual std::unique_ptr<Wall> MakeWall() const;

    /**
     * \brief Creates a maze game
     */
    void CreateMaze();
    void CreateMaze(Mazefactory* mf);
    void CreateMaze(std::shared_ptr<MazeBuilder> mb);
    void CreateMazebyFactoryMethods();
    std::unique_ptr<MazePrototypeFactory> MakePrototypeFactory();
private:
    /*!
     * \brief pointer to maze
     */
    std::unique_ptr<Maze> _maze;
};

class GOF_EXPORT BombedMazeGame : public MazeGame
{
public:
    BombedMazeGame();
    ~BombedMazeGame() override;
    std::unique_ptr<Room> MakeRoom(int rno) const override;
    std::unique_ptr<Wall> MakeWall() const override;
};

class GOF_EXPORT EnchantedMazeGame : public MazeGame
{
public:
    EnchantedMazeGame();
    ~EnchantedMazeGame() override;
    std::unique_ptr<Room> MakeRoom(int rno) const override;
protected:
    std::unique_ptr<Spell> CastSpell() const;
};

}}
#endif
