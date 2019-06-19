#ifndef _GOF_MAZEGAME_H_
#define _GOF_MAZEGAME_H_

#include <memory>
#include <string>
#include "gof_export.h"

namespace gof {

class Maze;
class Room;
class Door;
class Wall;
class Spell;
class MazeFactory;
class MazeBuilder;
class MazePrototypeFactory;
class MazePlayer;
enum class Direction;
/** This class can be used to create a Maze Game.
 * @ingroup Factory_Methods
 */
class GOF_EXPORT MazeGame
{
public:
    /// @brief MazeGame Constructor
    MazeGame();

    MazeGame(MazeGame&& rhs);
    MazeGame& operator=(MazeGame&& rhs);
    MazeGame(const MazeGame& rhs) = delete;
    MazeGame& operator=(const MazeGame& rhs) = delete;


    /// MazeGame Destructor
    virtual ~MazeGame();

    virtual std::unique_ptr<Maze> MakeMaze() const;
    virtual std::unique_ptr<Room> MakeRoom(int rno) const;
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
    virtual std::unique_ptr<Wall> MakeWall() const;

    /// \brief Creates a maze game
    void CreateMaze();
    void CreateMaze(MazeFactory* mf);
    void CreateMaze(std::ostream& out, std::shared_ptr<MazeBuilder> mb);
    void CreateMazebyFactoryMethods();

    void initGame(MazePlayer& player);
    void playGame(MazePlayer& player, Direction d);

private:
    std::unique_ptr<Maze> _maze;
};

/** Overrides factory methods to create RoomWithABomb.
 * @ingroup Factory_Methods
 */
class GOF_EXPORT BombedMazeGame : public MazeGame
{
public:
    BombedMazeGame();
    ~BombedMazeGame() override;
    std::unique_ptr<Room> MakeRoom(int rno) const override;
    std::unique_ptr<Wall> MakeWall() const override;
};

/** Overrides Factory methods to ceate EnchantedRoom
 * @ingroup Factory_Methods
 */
class GOF_EXPORT EnchantedMazeGame : public MazeGame
{
public:
    EnchantedMazeGame();
    ~EnchantedMazeGame() override;
    std::unique_ptr<Room> MakeRoom(int rno) const override;
protected:
    std::unique_ptr<Spell> CastSpell() const;
};

}
#endif
