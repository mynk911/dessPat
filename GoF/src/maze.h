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
     * \brief Access one of the four Sides of room
     * \param d specify direction
     * \return returns reference to MapSite in specified direction
     */
    MapSite* GetSide(Direction d) const;

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
    void SetSide(Direction d, MapSite* ms);

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
    MapSite* _sides[4];
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
    Door(Room* r1= nullptr, Room* r2= nullptr);
    /*!
     * \brief entry behaviour of door
     */
    void enter() override;

    /*!
     * \brief Other Side From door
     * \param r One of the room door opens to
     * \return Other room door opens to
     */
    Room* OtherSideFrom(Room* r);
private:
    /*!
     * \brief _room1 room connected by door
     */
    Room* _room1;
    /*!
     * \brief _room2 room connected by door
     */
    Room* _room2;
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
    void AddRoom(Room* r);

    /*!
     * \brief returns room with specified Room No
     * \param rn room no
     * \return refernce to room
     */
    Room* RoomNo(int rn) const;
private:
    std::vector<Room*> _maze;
};

#endif
