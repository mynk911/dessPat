/*!
 * \file mazefactory.h
 * \brief maze factory declarations
 * \author mayank bansal
 */

/*!
 * \brief Base class for Maze Factories
 */

#ifndef GOF_MAZEFACTORY_H_
#define GOF_MAZEFACTORY_H_

#include <memory>
#include "gof_export.h"

/*!
 * \namespace gof
 *
 * \brief main namespace for GoF lib.
 */
namespace gof {

/*!
 * \namespace creational
 *
 * \brief namespace for creational design patterns.
 */
namespace creational {

// forward declarations
class Maze;
class Room;
class Door;
class Wall;
class Spell;
class Bomb;

/*!
 * \class Mazefactory.
 * \brief The Mazefactory class. Singleton base for maze factories.
 */
class GOF_EXPORT Mazefactory
{
public:
    /*!
     * \brief destroy a mazefactory
     */
    virtual ~Mazefactory();
    /*!
     * \brief manages the MazeFactory object.
     */
    static Mazefactory* Instance();
    /*!
     * \brief make a maze.
     */
    virtual std::unique_ptr<Maze> MakeMaze() const;
    /*!
     * \brief make a room.
     */
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    /*!
     * \brief Make a Door.
     */
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    /*!
     * \brief Make a Wall.
     */
    virtual std::unique_ptr<Wall> MakeWall() const;
protected:
    /*!
     * \brief create a maze factory instance.
     */
    Mazefactory();
private:
    /// holds a unique MazeFactory instance.
    static std::unique_ptr<Mazefactory> _instance;
};

/*!
 * \class EnchantedMazefactory.
 * \inherits Mazefactory.
 *
 * \brief Mazefactory which can create enchanted rooms.
 */
class GOF_EXPORT EnchantedMazefactory : public Mazefactory
{
public:
    /*!
     * \brief Enchanted Maze factory constructor.
     */
    EnchantedMazefactory();
    /*!
     * \brief Enchanted Maze factory destructor.
     */
    ~EnchantedMazefactory() override;
    /*!
     * \brief MakeRoom
     */
    std::unique_ptr<Room> MakeRoom(int rn) const override;
protected:
    /*!
     * \brief Cast Spell
     */
    std::unique_ptr<Spell> CastSpell() const;
};

/*!
 * \class BombedMazefactory.
 * \inherits Mazefactory.
 *
 * \brief Mazefactory which can create rooms with a bomb.
 */
class GOF_EXPORT BombedMazeFactory : public Mazefactory
{
public:
    /*!
     * \brief Bombed Maze factory constructor.
     */
    BombedMazeFactory();

    /*!
     * \brief Bombed Maze factory destructor.
     */
    ~BombedMazeFactory() override;

    /*!
     * \brief MakeRoom
     */
    std::unique_ptr<Room> MakeRoom(int rn) const override;

    /*!
     * \brief MakeWall
     */
    std::unique_ptr<Wall> MakeWall() const override;
protected:
    /*!
     * \brief MakeBomb
     */
    std::unique_ptr<Bomb> MakeBomb(int n) const;
};

class GOF_EXPORT MazePrototypeFactory : public Mazefactory
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

}}

#endif // GOF_MAZEFACTORY_H_

