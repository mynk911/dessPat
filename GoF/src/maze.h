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

#define LOG_CONSTRUCTOR_DESTRUCTOR_CALLS

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
    virtual ~MapSite() = 0;
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

    /*!
      \brief Room destructor
     */
    ~Room();

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
private:
    /*!
     * \brief _roomNumber identifies room
     */
    int _roomNumber;
    /*!
     * \brief _sides holds four sides of a room
     */
    std::shared_ptr<MapSite> _sides[4];
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

    /*!
      \brief Wall destructor
     */
    ~Wall();

    /*!
     * \brief entry behaviour of wall
     */
    void enter() override;
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

    /*!
      \brief Door destructor
     */
    ~Door();
    /*!
     * \brief entry behaviour of door
     */
    void enter() override;

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

    /*!
     * \brief Maze destructor
     */
    ~Maze();

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

class EnchantedRoom : public Room
{
public:
    EnchantedRoom(int n, std::unique_ptr<Spell> s);
    virtual ~EnchantedRoom();
    void enter() override;

private:
    std::unique_ptr<Spell> _spell;
};
#endif
