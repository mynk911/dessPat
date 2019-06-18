/**
 *  @file mazefactory.h
 *  declarations for mazefactory.
 */

#ifndef GOF_MAZEFACTORY_H_
#define GOF_MAZEFACTORY_H_

#include <memory>
#include "gof_export.h"

/**
 * @namespace gof
 *
 * main namespace for GoF lib.
 * This namespace collects all the types and names related to GoF library.
 */
namespace gof {

// forward declarations
class Maze;
class Room;
class Door;
class Wall;
class Spell;
class Bomb;

/** Singleton base for abstract factories.
 *
 * @ingroup Abstract_Factory
 * @ingroup Singleton
 */
class GOF_EXPORT MazeFactory
{
public:
    /** @name Deleted Functions
     * Singleton cannot be copied, assigned or moved.
     */
    ///@{
    MazeFactory(const MazeFactory& other) = delete;
    MazeFactory& operator=(const MazeFactory& other) = delete;
    MazeFactory(MazeFactory&& other) = delete;
    MazeFactory& operator=(MazeFactory&& other) = delete;
    ///@}

    /** manages the single instance of MazeFactory.
     creates a mazefactory instance on first call. The type of object
     can be changed using environment variable MAZESTYLE. Subsequent calls
     return the same object.

     @returns pointer to MazeFactory.
     */
    static MazeFactory* Instance();

    /// creates and returns a Maze.
    virtual std::unique_ptr<Maze> MakeMaze() const;

    /** creates and returns a Room.
     @param  rn  room number to assign to room.
     */
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    
    /** creates and returns a Door.
     @param r1 Room room connected to this door.
     @param r2 Room room connected to this door.
     */
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, 
                                           std::shared_ptr<Room> r2) const;

    /// creates and returns a Wall.
    virtual std::unique_ptr<Wall> MakeWall() const;
protected:
    /** MazeFactory Constructor.
     Only One MazeFactory instance should exist. Hence calls to MazeFactory
     constructor can only be made by derived classes and Instance.
     */
    MazeFactory();
    /** MazeFactory destructor.
     */
    ~MazeFactory();
private:
    static MazeFactory* _instance;
};

/** @file mazefactory_private.h
 EnchantedMazeFactory,BombedMazeFactory and MazePrototypeFactory definitions.
*/

/** Factory class for enchanted mazes.
 EnchantedMazeFactory facilitates creation of enchanted mazes where rooms are
 bound by spells.
 @ingroup Abstract_Factory
 */
class EnchantedMazeFactory : public MazeFactory
{
    friend class MazeFactory;
public:
     ~EnchantedMazeFactory();
    /// creates and returns an EnchantedRoom.
    std::unique_ptr<Room> MakeRoom(int rn) const override;
protected:
    EnchantedMazeFactory();
    /// Creates a Spell for EnchantedRoom.
    std::unique_ptr<Spell> CastSpell() const;
};


/** Factory which can create rooms with a bomb.
 * @ingroup Abstract_Factory
 */
class BombedMazeFactory : public MazeFactory
{
    friend class MazeFactory;
public:
    ~BombedMazeFactory();
    /// creates and returns a RoomWithABomb.
    std::unique_ptr<Room> MakeRoom(int rn) const override;
    std::unique_ptr<Wall> MakeWall() const override;
protected:
    BombedMazeFactory();
    /// creates a Bomb counting down from n.
    std::unique_ptr<Bomb> MakeBomb(int n) const;
};

/** A MazeFactory initialized with prototype objects of MapSite.
 Objects are created by calling Clone on the prototype.
 @ingroup Prototype
*/
class GOF_EXPORT MazePrototypeFactory : public MazeFactory
{
public:
    MazePrototypeFactory(std::unique_ptr<Maze> m, std::unique_ptr<Room> r,
                         std::unique_ptr<Door> d, std::unique_ptr<Wall> w);
    ~MazePrototypeFactory();
    std::unique_ptr<Maze> MakeMaze() const;
    std::unique_ptr<Room> MakeRoom(int rno) const;
    std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    std::unique_ptr<Wall> MakeWall() const;
private:
    std::unique_ptr<Maze> _prototypeMaze;
    std::unique_ptr<Room> _prototypeRoom;
    std::unique_ptr<Door> _prototypeDoor;
    std::unique_ptr<Wall> _prototypeWall;
};

}

#endif // GOF_MAZEFACTORY_H_

