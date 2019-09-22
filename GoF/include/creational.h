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
    explicit Room(int roomNo);
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
    explicit Bomb (int n);
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

/** Singleton base for abstract factories.
 *
 * @ingroup Abstract_Factory
 * @ingroup Singleton
 */
class GOF_EXPORT MazeFactory
{
public:
    /** @name Deleted Functions
     * Singleton cannot be copied, assigned or moved.
     */
    ///@{
    MazeFactory(const MazeFactory& other) = delete;
    MazeFactory& operator=(const MazeFactory& other) = delete;
    MazeFactory(MazeFactory&& other) = delete;
    MazeFactory& operator=(MazeFactory&& other) = delete;
    ///@}

    /** manages the single instance of MazeFactory.
     creates a mazefactory instance on first call. The type of object
     can be changed using environment variable MAZESTYLE. Subsequent calls
     return the same object.

     @returns pointer to MazeFactory.
     */
    static MazeFactory* Instance();

    /// creates and returns a Maze.
    virtual std::unique_ptr<Maze> MakeMaze() const;

    /** creates and returns a Room.
     @param  rn  room number to assign to room.
     */
    virtual std::unique_ptr<Room> MakeRoom(int rn) const;
    
    /** creates and returns a Door.
     @param r1 Room room connected to this door.
     @param r2 Room room connected to this door.
     */
    virtual std::unique_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, 
                                           std::shared_ptr<Room> r2) const;

    /// creates and returns a Wall.
    virtual std::unique_ptr<Wall> MakeWall() const;
protected:
    /** MazeFactory Constructor.
     Only One MazeFactory instance should exist. Hence calls to MazeFactory
     constructor can only be made by derived classes and Instance.
     */
    MazeFactory();
    /** MazeFactory destructor.
     */
    ~MazeFactory();
private:
    static MazeFactory* _instance;
};

/** @file mazefactory_private.h
 EnchantedMazeFactory,BombedMazeFactory and MazePrototypeFactory definitions.
*/

/** Factory class for enchanted mazes.
 EnchantedMazeFactory facilitates creation of enchanted mazes where rooms are
 bound by spells.
 @ingroup Abstract_Factory
 */
class EnchantedMazeFactory : public MazeFactory
{
    friend class MazeFactory;
public:
     ~EnchantedMazeFactory();
    /// creates and returns an EnchantedRoom.
    std::unique_ptr<Room> MakeRoom(int rn) const override;
protected:
    EnchantedMazeFactory();
    /// Creates a Spell for EnchantedRoom.
    std::unique_ptr<Spell> CastSpell() const;
};


/** Factory which can create rooms with a bomb.
 * @ingroup Abstract_Factory
 */
class BombedMazeFactory : public MazeFactory
{
    friend class MazeFactory;
public:
    ~BombedMazeFactory();
    /// creates and returns a RoomWithABomb.
    std::unique_ptr<Room> MakeRoom(int rn) const override;
    std::unique_ptr<Wall> MakeWall() const override;
protected:
    BombedMazeFactory();
    /// creates a Bomb counting down from n.
    std::unique_ptr<Bomb> MakeBomb(int n) const;
};

/** A MazeFactory initialized with prototype objects of MapSite.
 Objects are created by calling Clone on the prototype.
 @ingroup Prototype
*/
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

enum class Direction;
/** Base class for Builder classes.
 * defines a common interface for builder classes.
 * @ingroup Builder
 */
class GOF_EXPORT MazeBuilder
{
public:
    /// MazeBuilder Destructor.
    virtual ~MazeBuilder();
    /// Creates a Maze.
    virtual void BuildMaze() = 0;

    /** Creates a Room.
     * @param rno number to be assigned to room.
     */
    virtual void BuildRoom(int rno) = 0;
    /** Creates a Door.
     * @param r1 number assigned to connected Room.
     * @param r2 number assigned to connected Room.
     */
    virtual void BuildDoor(int r1,int r2) = 0;
    /// Returns the final assembled Maze object.
    virtual std::unique_ptr<Maze> GetMaze() = 0;
protected:
    /// MazeBuilder destructor.
    MazeBuilder();
};

/** assembles a Simple MAze from given rooms and doors.
 * @ingroup Builder
 */
class GOF_EXPORT StandardMazeBuilder : public MazeBuilder
{
public:
    StandardMazeBuilder();
    ~StandardMazeBuilder() override;
    void BuildMaze() override;
    void BuildRoom(int rno) override;
    void BuildDoor(int r1, int r2) override;
    std::unique_ptr<Maze> GetMaze() override;
protected:
    /// finds common wall between two given rooms.
    Direction CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
    std::unique_ptr<Maze> _maze;
};

/** a special builder example which simply counts doors and rooms in a plan.
 * @ingroup Builder
 */
class GOF_EXPORT CountingMazeBuilder : public MazeBuilder
{
public:
    CountingMazeBuilder();
    ~CountingMazeBuilder() override;
    void BuildRoom(int rno) override;
    void BuildDoor(int r1, int r2) override;
    void BuildMaze() override;
    std::unique_ptr<Maze> GetMaze() override;
    /** Get Counts of doors and rooms.
     * @param rooms[out] number of rooms.
     * @param doors[out] number of doors.
     */
    void GetCounts(int& rooms, int& doors) const;
private:
    int _rooms;
    int _doors;
};

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
