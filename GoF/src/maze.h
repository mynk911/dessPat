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
namespace gof {
namespace creational {

/*!
 * \brief The Direction enum
 * Specifies possible directions as North, West, East or South
 */
enum class Direction {
    North,
    South,
    East,
    West
};

/*!
 * \brief The MapSite class
 * An abstract class that provides interface for all mapsites
 */
class MapSite
{
public:
    /*!
     * \brief controls entry behaviour for a mapsite
     */
    virtual void enter() = 0;
    virtual ~MapSite();
    MapSite();
    MapSite(MapSite&& other);
    MapSite& operator=(MapSite&& other);
    MapSite(const MapSite& other);
    MapSite& operator=(const MapSite& other);
};

/*!
 * \brief The Room class
 * A room inside a maze
 */
class Room: public MapSite {
public:
    /*!
     * \brief Room constructor
     * \param roomNo to uniquely identify a room
     */
    Room(int roomNo);
    Room();
    Room(Room&& other);
    Room& operator=(Room&& other);
    Room(const Room& other);
    Room& operator=(const Room& other);


    /*!
      \brief Room destructor
     */
    ~Room() override;

    /*!
     * \brief Access one of the four Sides of room
     * \param d specify direction
     * \return returns reference to MapSite in specified direction
     */
    std::shared_ptr<MapSite> GetSide(Direction d) const;

    /*!
     * \brief Get RoomNo
     * \return room numbers
     */
    int GetRoomNo() const;

    /*!
     * \brief Set one of the four Sides of room
     * \param d specify direction
     * \param ms refernce to a mapsite
     */
    void SetSide(Direction d, std::shared_ptr<MapSite> ms);

    /*!
     * \brief entry behaviour of a room
     */
    void enter() override;
    virtual std::unique_ptr<Room> Clone() const;
    virtual void Initialize(int rno);
private:
    /*!
     * \brief _roomNumber identifies room
     */
    int _roomNumber;
    /*!
     * \brief _sides holds four sides of a room
     */
    std::vector<std::shared_ptr<MapSite>> _sides;
};

/*!
 * \brief The Wall class
 * A mapsite which represents wall
 */
class Wall : public MapSite
{
public:
    /*!
     * \brief Wall constructor
     */
    Wall();
    Wall(Wall&& other);
    Wall& operator=(Wall&& other);
    Wall(const Wall& other);
    Wall& operator=(const Wall& other);

    /*!
      \brief Wall destructor
     */
    ~Wall() override;

    /*!
     * \brief entry behaviour of wall
     */
    void enter() override;
    virtual std::unique_ptr<Wall> Clone() const;
};

/*!
 * \brief The Door class
 * A mapsite which represents a door
 */
class Door: public MapSite {
public:
    /*!
     * \brief Door constructor
     * \param r1 room one
     * \param r2 room two
     */
    Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    Door();
    Door(Door&& other);
    Door& operator=(Door&& other);
    Door(const Door& other);
    Door& operator=(const Door& other);
    /*!
      \brief Door destructor
     */
    ~Door() override;
    /*!
     * \brief entry behaviour of door
     */
    void enter() override;
    virtual void Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    virtual std::unique_ptr<Door> Clone() const;
    /*!
     * \brief Other Side From door
     * \param r One of the room door opens to
     * \return Other room door opens to
     */
    std::shared_ptr<Room> OtherSideFrom(std::shared_ptr<Room> r);
private:
    /*!
     * \brief _room1 room connected by door
     */
    std::weak_ptr<Room> _room1;
    /*!
     * \brief _room2 room connected by door
     */
    std::weak_ptr<Room> _room2;
    /*!
     * \brief _isOpen wether the room is locked
     */
    bool _isOpen;
};

/*!
 * \brief The Maze class
 * A collection of map sites
 */
class Maze
{
public:
    /*!
     * \brief Maze constructor
     */
    Maze();
    Maze(Maze&& other);
    Maze& operator=(Maze&& other);
    Maze(const Maze& other);
    Maze& operator=(const Maze& other);
    /*!
     * \brief Maze destructor
     */
    virtual ~Maze();

    /*!
     * \brief Add Room to maze
     * \param r reference to a room
     */
    void AddRoom(std::shared_ptr<Room> r);

    /*!
     * \brief returns room with specified Room No
     * \param rn room no
     * \return refernce to room
     */
    std::shared_ptr<Room> RoomNo(int rn) const;
    virtual std::unique_ptr<Maze> Clone() const;
private:
    std::vector<std::shared_ptr<Room>> _rooms;
};

/* \brief spell class
 *
 * create a spell object with a question and answer string.
 */
class Spell
{
public:
    Spell (std::string q, std::string a);
    virtual ~Spell ();
    bool dispell(std::string s);
private:
    std::string q;
    std::string a;
};

/*!
 *  \brief room with a spell on it
 */
class EnchantedRoom : public Room
{
public:
    EnchantedRoom(int n, std::unique_ptr<Spell> s);
    ~EnchantedRoom() override;
    void enter() override;

private:
    std::unique_ptr<Spell> _spell;
};

/*!
 * \brief Bomb class
 */
class Bomb
{
public:
    Bomb (int n);
    virtual ~Bomb ();
    int GetDetonationTime();
private:
    int _time;
};

/*!
 * \brief Room With A Bomb
 */
class RoomWithABomb : public Room
{
public:
    RoomWithABomb (int n, std::unique_ptr<Bomb> b);
    ~RoomWithABomb () override;
    void enter() override;

private:
    std::unique_ptr<Bomb> _bomb;
};

/*!
 * \brief Bombed Wall class
 */
class BombedWall : public Wall
{
public:
    BombedWall ();
    ~BombedWall () override;
    void enter() override;
};
}}

#endif
