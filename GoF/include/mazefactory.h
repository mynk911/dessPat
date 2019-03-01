/*!
 * \file mazefactory.h
 * \brief maze factory declarations
 * \author mayank bansal
 */

/*!
 * \brief Base class for Maze Factories
 */

#ifndef _GOF_MAZEFACTORY_H_
#define _GOF_MAZEFACTORY_H_

#include <memory>
#include "gof_export.h"
namespace gof {
namespace creational {

class Maze;
class Room;
class Door;
class Wall;
class Spell;
class Bomb;

class GOF_EXPORT Mazefactory
{
public:
    virtual ~Mazefactory();
    static Mazefactory* Instance();
    virtual std::unique_ptr<Maze> MakeMaze() const;
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    virtual std::unique_ptr<Wall> MakeWall() const;
protected:
    Mazefactory();
private:
    static std::unique_ptr<Mazefactory> _instance;
};

class GOF_EXPORT EnchantedMazefactory : public Mazefactory
{
public:
    EnchantedMazefactory();
    ~EnchantedMazefactory() override;
    std::unique_ptr<Room> MakeRoom(int rn) const override;
protected:
    std::unique_ptr<Spell> CastSpell() const;
};

class GOF_EXPORT BombedMazeFactory : public Mazefactory
{
public:
    BombedMazeFactory();
    ~BombedMazeFactory() override;
    std::unique_ptr<Room> MakeRoom(int rn) const override;
    std::unique_ptr<Wall> MakeWall() const override;
protected:
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

#endif /* ifndef _GOF_MAZEFACTORY_H_ */

