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

class Maze;
class Room;
class Door;
class Wall;
class Spell;

class GOF_EXPORT Mazefactory
{
public:
    Mazefactory();
    virtual ~Mazefactory();
    virtual std::unique_ptr<Maze> MakeMaze() const;
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    virtual std::unique_ptr<Wall> MakeWall() const;
};

class GOF_EXPORT EnchantedMazefactory : public Mazefactory
{
public:
    EnchantedMazefactory();
    virtual ~EnchantedMazefactory();
    virtual std::unique_ptr<Room> MakeRoom(int rn) const override;
protected:
    std::unique_ptr<Spell> CastSpell() const;
};
#endif /* ifndef _GOF_MAZEFACTORY_H_ */


