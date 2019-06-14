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

/** @Defgroup Creational  creational design patterns.
 *
 * Examples of creational design patterns. Central to all examples is 
 * the composite Type heirarchy MapSite. All examples build objects of 
 * MapSite type to demonstrate pros and cons of different creational 
 * patterns and applicability of each to particular scenarios. MazeGame 
 * brings creation and MapSite code together. It also contains code for 
 * Factory Method pattern.
 *
 */

/** @Defgroup Abstract_Factory Abstract Factory Pattern Examples.
 *@Ingroup Creational
 *
 * Abstract Factory classes create a family of related objects. In our
 * example MazeFactory creates objects of type Maze, Room, Wall and Door.
 * All these objects together constitute a maze. EnchantedMazeFactory and
 * BombedMazeFactory override MazeFactory to create EnchantedRooms and 
 * RoomWithabomb respectively instead of normal rooms.
 *
 * The pattern is not suitable for our composite type since objects in maze
 * family do not form segregated sub families. For example we could have a
 * maze with both bombed and enchanted rooms. Abstract Factory works best 
 * when classes form a family with respect to a property and subclassing one
 * entails subclassing all.
 */

/** @Defgroup Singleton  Singleton Pattern classes.
 *
 * 
 */

/*!
 * \namespace gof
 *
 * \brief main namespace for GoF lib.
 * 
 * This namespace collects all the types and names related to GoF library.
 */
namespace gof {

/*!
 * \namespace creational
 *
 * \brief namespace for 
 */
namespace creational {

// forward declarations
class Maze;
class Room;
class Door;
class Wall;
class Spell;
class Bomb;

/** @Brief Singleton base for Maze factories.
 *
 * MazeFactory heirarchy demonstrates singleton, factory and prototype
 * design patterns. Base class is a singleton. This ensures that only one
 * MazeFactory object exists. Derived classes BombedMazeFactory and
 * EnchantedMazeFactory demonstrate factory pattern while PrototypeMaze-
 * Factory shows the use of prototype pattern.
 */
class GOF_EXPORT MazeFactory
{
public: 
/** @Brief MazeFactory destructor.
 */
    virtual ~MazeFactory();
    
/** @Brief manages single instance of MazeFactory.
 */
    static MazeFactory* Instance();

/** @Brief Factory method for creating Maze. 
 */
    virtual std::unique_ptr<Maze> MakeMaze() const;
/** @Brief Factory method for creating Room.
 */    
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    
/** @Brief Factory method for creating Door.
 */
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, 
					   std::shared_ptr<Room> r2) const;
/** @Brief Factory Method for creating Wall.
 */
    virtual std::unique_ptr<Wall> MakeWall() const;
protected:
/** @Brief MazeFactory Constructor.
 */
    MazeFactory();
private:
    /// holds a unique MazeFactory instance.
    static std::unique_ptr<MazeFactory> _instance;
};

    
/** @Brief Factory class for enchanted mazes.
 * 
 * While MazeFactory helps us create basic mazes, EnchantedMazeFactory 
 * facilitates creation of enchanted mazes where rooms are bound by spells. 
 * If we have code to create maze of certain design as in MazeGame::createMaze 
 * just passing in EnchantedMazeFactory allows for creation of enchanted mazes 
 * without any code changes. 
 */
class GOF_EXPORT EnchantedMazeFactory : public MazeFactory
{
public:
    
    EnchantedMazeFactory();
    /*!
     * \brief Enchanted Maze factory destructor.
     */
    ~EnchantedMazeFactory() override;
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
class GOF_EXPORT BombedMazeFactory : public MazeFactory
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

}}

#endif // GOF_MAZEFACTORY_H_

