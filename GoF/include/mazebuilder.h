/*!
 * \file mazebuilder.h
 * \brief contains mazebuilder classes

   provide builder classes to create mazes from mapsites.
   \author Mayank Bansal
 */

#ifndef _GOF_MAZE_BUILDER_H_
#define _GOF_MAZE_BUILDER_H_

#include <memory>

namespace gof {

class Maze;
class Room;
enum class Direction;
/** Base class for Builder classes.
 * defines a common interface for builder classes.
 * @ingroup Builder
 */
class MazeBuilder
{
public:
    /// MazeBuilder Destructor.
    virtual ~MazeBuilder();
    /// Creates a Maze.
    virtual void BuildMaze() = 0;

    /** Creates a Room.
     * @param rno number to be assigned to room.
     */
    virtual void BuildRoom(int rno) = 0;
    /** Creates a Door.
     * @param r1 number assigned to connected Room.
     * @param r2 number assigned to connected Room.
     */
    virtual void BuildDoor(int r1,int r2) = 0;
    /// Returns the final assembled Maze object.
    virtual std::unique_ptr<Maze> GetMaze() = 0;
protected:
    /// MazeBuilder destructor.
    MazeBuilder();
};

/** assembles a Simple MAze from given rooms and doors.
 * @ingroup Builder
 */
class StandardMazeBuilder : public MazeBuilder
{
public:
    StandardMazeBuilder();
    ~StandardMazeBuilder() override;
    void BuildMaze() override;
    void BuildRoom(int rno) override;
    void BuildDoor(int r1, int r2) override;
    std::unique_ptr<Maze> GetMaze() override;
protected:
    /// finds common wall between two given rooms.
    Direction CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    std::unique_ptr<Maze> _maze;
};

/** a special builder example which simply counts doors and rooms in a plan.
 * @ingroup Builder
 */
class CountingMazeBuilder : public MazeBuilder
{
public:
    CountingMazeBuilder();
    ~CountingMazeBuilder() override;
    void BuildRoom(int rno) override;
    void BuildDoor(int r1, int r2) override;
    /** Get Counts of doors and rooms.
     * @param rooms[out] number of rooms.
     * @param doors[out] number of doors.
     */
    void GetCounts(int& rooms, int& doors) const;
private:
    int _rooms;
    int _doors;
};

}
#endif
