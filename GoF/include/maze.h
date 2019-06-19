/*!
  \file maze.h
  \brief contains declarations for map sites used in a a maze game.

  this file contains a class hierarchy for different MapSites used
  in a MazeGame.
  \author Mayank Bansal
  */
#ifndef GOF_MAZE_H_
#define GOF_MAZE_H_


#include <vector>
#include <memory>
#include <string>

#include "gof_export.h"

namespace gof {

class MazePlayer;
class MazeGame;

/// Specifies possible directions as North, West, East or South
enum class Direction {
    North,
    South,
    East,
    West
};

/** An abstract class that provides interface for all mapsites
 * @ingroup Creational
*/
class GOF_EXPORT MapSite
{
public:
    /// controls entry behaviour for mapsite
    virtual void enter(MazePlayer& player) = 0;
    virtual ~MapSite();
    MapSite();
    MapSite(MapSite&& other);
    MapSite& operator=(MapSite&& other);
    MapSite(const MapSite& other);
    MapSite& operator=(const MapSite& other);
};

/** A room inside a maze
 * @ingroup Creational
 */
class GOF_EXPORT Room: public MapSite {
public:
    /** Room constructor
     * @param roomNo to uniquely identify a room
     */
    Room(int roomNo);
    Room();
    Room(Room&& other);
    Room& operator=(Room&& other);
    Room(const Room& other);
    Room& operator=(const Room& other);

     ///Room destructor
    ~Room() override;

    /** Access one of the four Sides of room
     * @param d specify direction
     * @return returns reference to MapSite in specified direction
     */
    std::shared_ptr<MapSite> GetSide(Direction d) const;

    /** Get RoomNo
     * @return room numbers
     */
    int GetRoomNo() const;

    /** Set one of the four Sides of room
     * @param d specify direction
     * @param ms refernce to a mapsite
     */
    void SetSide(Direction d, std::shared_ptr<MapSite> ms);

    void enter(MazePlayer& player) override;
    virtual std::unique_ptr<Room> Clone() const;
    virtual void Initialize(int rno);
private:
    int _roomNumber;
    std::vector<std::shared_ptr<MapSite>> _sides;
};

/** A mapsite which represents wall
 * @ingroup Creational
 */
class GOF_EXPORT Wall : public MapSite
{
public:
    /// Wall constructor
    Wall();
    Wall(Wall&& other);
    Wall& operator=(Wall&& other);
    Wall(const Wall& other);
    Wall& operator=(const Wall& other);

    /// Wall destructor
    ~Wall() override;

    void enter(MazePlayer& player) override;
    virtual std::unique_ptr<Wall> Clone() const;
};

/** A mapsite which represents a door
 * @ingroup Creational
 */
class GOF_EXPORT Door: public MapSite {
public:
    /** Door constructor
     * @param r1 room one
     * @param r2 room two
     */
    Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    Door();
    Door(Door&& other);
    Door& operator=(Door&& other);
    Door(const Door& other);
    Door& operator=(const Door& other);
    /// Door destructor
    ~Door() override;
    void enter(MazePlayer& player) override;
    virtual void Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    virtual std::unique_ptr<Door> Clone() const;
    /** Other Side From door
     * @param r One of the room door opens to
     * @return Other room door opens to
     */
    std::shared_ptr<Room> OtherSideFrom(int r);
private:
    std::weak_ptr<Room> _room1;
    std::weak_ptr<Room> _room2;
    bool _isOpen;
};

/** A collection of map sites
 * @ingroup Creational
 */
class GOF_EXPORT Maze
{
public:
    /// Maze constructor
    Maze();
    Maze(Maze&& other);
    Maze& operator=(Maze&& other);
    Maze(const Maze& other);
    Maze& operator=(const Maze& other);
    /// Maze destructor
    virtual ~Maze();

    /** Add Room to maze
     * @param r reference to a room
     */
    void AddRoom(std::shared_ptr<Room> r);

    /** returns room with specified Room No
     * @param rn room no
     * @return refernce to room
     */
    std::shared_ptr<Room> RoomNo(int rn) const;
    virtual std::unique_ptr<Maze> Clone() const;
private:
    std::vector<std::shared_ptr<Room>> _rooms;
};


/** create a spell object with a question and answer string.
 * @ingroup Creational
 */
class Spell
{
public:
    /// create a spell object
    Spell (std::string q, std::string a);
    /// destroys a spell object
    virtual ~Spell ();
    /** dispell this spell
     * if provided string is correct the spell is dispelled
     * @param s answer string
     * @return true if s == answer
     *         false otherwise
     */
    bool dispell(std::string s);
private:
    std::string q;
    std::string a;
};

/** room with a spell on it
 * @ingroup Creational
 */
class EnchantedRoom : public Room
{
public:
    /** Enchanted room consructor *
     * create an enchanted room.Enchanted rooms need a spell to be broken.
     * @param n room number
     * @param s spell
     */
    EnchantedRoom(int n, std::unique_ptr<Spell> s);
    /// destroys an enchanted room
    ~EnchantedRoom() override;
    void enter(MazePlayer& player) override;

private:
    std::unique_ptr<Spell> _spell;
};

/** Bomb class
 * @ingroup Creational
 */
class Bomb
{
public:
    Bomb (int n);
    virtual ~Bomb ();
    /** Get Detonation Time
     * @return detonation time
     */
    int GetDetonationTime();
private:
    int _time;
};

/** Room With A Bomb
 * @ingroup Creational
 */
class RoomWithABomb : public Room
{
public:
    /** Create Room With A Bomb
     * @param n room no
     * @param b bomb
     */
    RoomWithABomb (int n, std::unique_ptr<Bomb> b);
    /// Destroy Room With A Bomb
    ~RoomWithABomb () override;
    void enter(MazePlayer& player) override;

private:
    std::unique_ptr<Bomb> _bomb;
};

/** Bombed Wall class
 * @ingroup Creational
 */
class BombedWall : public Wall
{
public:
    BombedWall ();
    ~BombedWall () override;
    void enter(MazePlayer& player) override;
};

class GOF_EXPORT MazePlayer{
public:
    int getLocation() const;
    void setLocation(int value);
    virtual void status(std::string s) = 0;
    virtual ~MazePlayer();
    MazePlayer();
    MazePlayer(const MazePlayer& other);
    MazePlayer& operator=(const MazePlayer& other);
private:
    int location;
};

class GOF_EXPORT MazeTestPlayer : public MazePlayer{
public:
    std::string _status;
    void status(std::string s) override;
};

}

#endif
