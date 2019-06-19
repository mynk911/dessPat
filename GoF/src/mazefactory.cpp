#include <iostream>
#include <cstring>

#include "dbg.h"
#include "mazefactory.h"
#include "maze.h"

namespace gof {

MazeFactory* MazeFactory::_instance;

MazeFactory* MazeFactory::Instance()
{
    if(_instance == nullptr)
    {
        const char* mazestyle = getenv("MAZESTYLE");
        if(mazestyle == nullptr) mazestyle = "default";
        if(strcmp(mazestyle, "bombed") == 0)
            _instance = new BombedMazeFactory;
        else if(strcmp(mazestyle, "enchanted") == 0)
            _instance = new EnchantedMazeFactory;
	// TODO : add MazePrototypeFactory case here.
        else
            _instance = new MazeFactory;
    }
    return _instance;
}



MazeFactory::MazeFactory()
{
    debug("creating MazeFactory");
}



MazeFactory::~MazeFactory()
{
    debug("destroying MazeFactory");
    if(_instance != nullptr)
    {
        // delete the object after zeroing out the static
        // instance.
        MazeFactory* ptr = _instance;
        _instance = nullptr;
        delete ptr;
    }
}

std::unique_ptr<Maze> MazeFactory::MakeMaze() const
{
    return std::make_unique<Maze>();
}

std::unique_ptr<Room> MazeFactory::MakeRoom(int rn) const
{
    return std::make_unique<Room>(rn);
}

std::unique_ptr<Door> MazeFactory::MakeDoor(std::shared_ptr<Room> r1,
                                            std::shared_ptr<Room> r2) const
{
    return std::make_unique<Door>(r1, r2);
}

std::unique_ptr<Wall> MazeFactory::MakeWall() const
{
    return std::make_unique<Wall>();
}

EnchantedMazeFactory::EnchantedMazeFactory()
    :MazeFactory()
{
    debug("creating enchanted maze factory");
}

EnchantedMazeFactory::~EnchantedMazeFactory()
{
   debug("destroying enchanted maze factory");
}


std::unique_ptr<Room> EnchantedMazeFactory::MakeRoom(int rn) const
{
    return std::make_unique<EnchantedRoom>(rn, CastSpell());
}

std::unique_ptr<Spell> EnchantedMazeFactory::CastSpell() const
{
    return std::make_unique<Spell>("qwer","test");
}

BombedMazeFactory::BombedMazeFactory()
    :MazeFactory()
{
    debug("creating bombed maze factory");
}

BombedMazeFactory::~BombedMazeFactory()
{
    debug("destroying Bombed maze factory");
}

std::unique_ptr<Room> BombedMazeFactory::MakeRoom(int n) const
{
    return std::make_unique<RoomWithABomb>(n, MakeBomb(n));
}

std::unique_ptr<Wall> BombedMazeFactory::MakeWall() const
{
    return std::make_unique<BombedWall>();
}

std::unique_ptr<Bomb> BombedMazeFactory::MakeBomb(int n) const
{
    return std::make_unique<Bomb>(n);
}

MazePrototypeFactory::MazePrototypeFactory(std::unique_ptr<Maze> m, std::unique_ptr<Room> r,
                                           std::unique_ptr<Door> d, std::unique_ptr<Wall> w)
    : MazeFactory (),
      _prototypeMaze(std::move(m)),
      _prototypeRoom(std::move(r)),
      _prototypeDoor(std::move(d)),
      _prototypeWall(std::move(w))
{
    debug("Creating maze prototype factory");
}

MazePrototypeFactory::~MazePrototypeFactory()
{
    debug("Destroying maze prototype factory");
}

std::unique_ptr<Maze> MazePrototypeFactory::MakeMaze() const
{
    return _prototypeMaze->Clone();
}

std::unique_ptr<Room> MazePrototypeFactory::MakeRoom(int rno) const
{
    std::unique_ptr<Room> room = _prototypeRoom->Clone();
    room->Initialize(rno);
    return room;
}

std::unique_ptr<Door> MazePrototypeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    std::unique_ptr<Door> door = _prototypeDoor->Clone();
    door->Initialize(r1, r2);
    return door;
}

std::unique_ptr<Wall> MazePrototypeFactory::MakeWall() const
{
    return _prototypeWall->Clone();
}

}
