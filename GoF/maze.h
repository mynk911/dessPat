#ifndef GOF_MAZE_H_
#define GOF_MAZE_H_

#include <vector>

enum class Direction;

class MapSite
{
public:
    virtual void enter() = 0;
};

class Room: public MapSite {
public:
    Room(int roomNo);
    MapSite* GetSide(Direction) const;
    void SetSide(Direction, MapSite*);
    void enter() override;
private:
    int _roomNumber;
    MapSite* _sides[4];
};

class Wall : public MapSite
{
public:
    Wall();
    void enter() override;
};

class Door: public MapSite {
public:
    Door(Room* = nullptr, Room* = nullptr);
    void enter() override;
    Room* OtherSideFrom(Room*);
private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class Maze
{
public:
    Maze();
    void AddRoom(Room*);
    Room* RoomNo(int) const;
private:
    std::vector<Room*> _maze;
};

#endif
