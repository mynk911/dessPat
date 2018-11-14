/*!
 * \file mazebuilder.h
 * \brief contains mazebuilder classes

   provide builder classes to create mazes from mapsites.
   \author Mayank Bansal
 */

#ifndef _GOF_MAZE_BUILDER_H_
#define _GOF_MAZE_BUILDER_H_

#include <memory>

class Maze;
class Room;
enum class Direction;
/*!
 * \brief The MazeBuilder class - interface for maze builder classes
 */
class MazeBuilder
{
public:
    virtual ~MazeBuilder();
    virtual void BuildMaze() {}
    virtual void BuildRoom(int rno) {}
    virtual void BuildDoor(int r1,int r2) {}
    virtual std::unique_ptr<Maze> GetMaze();
protected:
    MazeBuilder();
};

class StandardMazeBuilder : public MazeBuilder
{
public:
    StandardMazeBuilder();
    ~StandardMazeBuilder();
    void BuildMaze() override;
    void BuildRoom(int rno) override;
    void BuildDoor(int r1, int r2) override;
    std::unique_ptr<Maze> GetMaze() override;
protected:
    Direction CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    std::unique_ptr<Maze> _maze;
};
#endif
