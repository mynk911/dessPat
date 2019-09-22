#include <iostream>
#include <stdexcept>

#include "creational.h"
#include "dbg.h"

namespace gof {

MapSite::MapSite()
{
    debug("Creating Mapsite");
}

MapSite::MapSite(MapSite&& other)
{
    debug("Creating MapSite : move");
}

MapSite& MapSite::operator=(MapSite&& other)
{
    debug("assigning MapSite : move");
    return *this;
}

MapSite::MapSite(const MapSite& other)
{
    debug("Creating MapSite : copy");
}

MapSite& MapSite::operator=(const MapSite& other)
{
    debug("assigning MapSite : copy");
    return *this;
}

MapSite::~MapSite()
{
    debug("Destroying MapSite");
}

Room::Room(int roomNo)
    :_roomNumber(roomNo),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("Creating Room ");
}

Room::Room()
    :_roomNumber(0),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("default Creating Room ");
}

Room::Room(Room&& other)
    :MapSite (std::move(other)),
      _roomNumber(std::move(other._roomNumber)),
      _sides(std::move(other._sides))
{
    debug("Creating Room : move");
}

Room& Room::operator=(Room&& other)
{
    MapSite::operator=(std::move(other));
    _roomNumber = std::move(other._roomNumber);
    _sides = std::move(other._sides);
    debug("assigning Room : move");
    return *this;
}

Room::Room(const Room& other)
    :MapSite (other),
      _roomNumber(other._roomNumber),
      _sides{nullptr,nullptr,nullptr,nullptr}
{
    debug("Creating Room : copy");
}

Room& Room::operator=(const Room& other)
{
    MapSite::operator=(other);
    _roomNumber = other._roomNumber;
    _sides = {nullptr,nullptr,nullptr,nullptr};
    debug("assigning Room : copy");
    return *this;
}

Room::~Room()
{
    debug("Destroying Room ");
}


std::shared_ptr<MapSite> Room::GetSide(Direction d) const
{
    return _sides[static_cast<int>(d)];
}

int Room::GetRoomNo() const
{
    return _roomNumber;
}

void Room::SetSide(Direction d, std::shared_ptr<MapSite> ms)
{
    auto mapsite = dynamic_cast<Room *>(ms.get());
    if(mapsite == nullptr)
        _sides[static_cast<int>(d)] = ms;
    else throw std::invalid_argument("rooms cannot contain other rooms");
}

std::unique_ptr<Room> Room::Clone() const
{
    return std::make_unique<Room>(*this);
}

void Room::Initialize(int rno)
{
    _roomNumber = rno;
}

// for now the implementation simply prints _roomNumber as we are only
//  interested in creation of mazes
// TODO: add player class and make enter take it as argument to change location
// on entering room
void Room::enter(MazePlayer& player)
{
    player.setLocation(_roomNumber);
    std::string s = "Room:";
    s += std::to_string(_roomNumber);
    player.status(s);
}

Wall::Wall()
{
    debug("Creating Wall");
}

Wall::Wall(Wall&& other)
    :MapSite (std::move(other))
{
    debug("Creating Wall : move");
}

Wall& Wall::operator=(Wall&& other)
{
    MapSite::operator=(std::move(other));
    debug("assigning Wall : move");
    return *this;
}

Wall::Wall(const Wall& other)
    :MapSite (std::move(other))
{
    debug("Creating Wall : copy");
}

Wall& Wall::operator=(const Wall& other)
{
    MapSite::operator=(other);
    debug("assigning Wall : copy");
    return *this;
}

Wall::~Wall()
{
    debug("Destroying Wall");
}

std::unique_ptr<Wall> Wall::Clone() const
{
    return std::make_unique<Wall>(*this);
}

void Wall::enter(MazePlayer& player)
{
    player.status("Wall");
}

Door::Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
    :_room1(r1),
     _room2(r2),
     _isOpen(true)
{
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
        debug("Creating Door %d %d", tr1->GetRoomNo(), tr2->GetRoomNo());
    else
        throw std::runtime_error("Door Constructor: Rooms do not exist!!");
}

Door::Door()
    :_room1(std::weak_ptr<Room>()),
      _room2(std::weak_ptr<Room>()),
      _isOpen(false)
{
    debug("Creating Door!!");
}

Door::Door(Door&& other)
    :MapSite (std::move(other)),
      _room1(std::move(other._room1)),
    _room2(std::move(other._room2))
{
    debug("Creating door : move");
}

Door& Door::operator=(Door&& other)
{
    MapSite::operator=(std::move(other));
    _room1 = std::move(other._room1);
    _room2 = std::move(other._room2);
    debug("assigning Wall : move");
    return *this;
}

Door::Door(const Door& other)
    :MapSite (other),
      _room1(std::weak_ptr<Room>()),
    _room2(std::weak_ptr<Room>())
{
    debug("Creating door : copy");
}

Door& Door::operator=(const Door& other)
{
    MapSite::operator=(other);
    _room1 = std::weak_ptr<Room>();
    _room2 = std::weak_ptr<Room>();
    debug("assigning door : copy");
    return *this;
}

std::unique_ptr<Door> Door::Clone() const
{
    return std::make_unique<Door>(*this);
}

void Door::Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    _room1 = r1;
    _room2 = r2;
}

Door::~Door()
{
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    debug("Destroying Door %d  %d", tr1->GetRoomNo(), tr2->GetRoomNo());
    else
    debug("Destroying Door");
}

std::shared_ptr<Room> Door::OtherSideFrom(int r)
{
    auto tr1 = _room1.lock();
    auto tr2 = _room2.lock();
    if(tr1 != nullptr && tr2 != nullptr)
    {
        if(r == tr1->GetRoomNo())
            return tr2;
        else if(r == tr2->GetRoomNo())
            return tr1;
    }
    return nullptr;
}

void Door::enter(MazePlayer& player)
{
    if(_isOpen)
        OtherSideFrom(player.getLocation())->enter(player);
    else
        player.status("Door Locked");
}

Maze::Maze()
{
    debug("Creating Maze");
}

Maze::Maze(Maze&& other)
    : _rooms(std::move(other._rooms))
{
    debug("Creating Maze : move");
}

Maze& Maze::operator=(Maze&& other)
{
    _rooms = std::move(other._rooms);
    debug("assigning Maze : move");
    return *this;
}

Maze::Maze(const Maze& other)
{
    debug("Creating Maze : copy");
}

Maze& Maze::operator=(const Maze& other)
{
    debug("assigning Maze : copy");
    return *this;
}

Maze::~Maze()
{
    debug("Destroying Maze");
}

std::unique_ptr<Maze> Maze::Clone() const
{
    return std::make_unique<Maze>(*this);
}

void Maze::AddRoom(std::shared_ptr<Room> r)
{
    auto rn = static_cast<std::vector<Room*>::size_type>(r->GetRoomNo());
    if(rn > 0 && _rooms.size() == rn-1)
        _rooms.push_back(r);
    else
        throw std::invalid_argument("MazeGame : Failed to add Room\n"
                                    "Room numbers should be added in increaing"
                                    " order of positive room numbers starting"
                                    " at Room no 1");
}

std::shared_ptr<Room> Maze::RoomNo(int rn) const
{
    auto rno = static_cast<std::vector<Room*>::size_type>(rn);
    if(rn > 0 && _rooms.size() >= rno)
        return _rooms[rno-1];
    else
        throw std::invalid_argument("Room numbers should be in valid range");
}


Spell::Spell(std::string q,std::string a)
    : q(q),
      a(a)
{
    debug("creating a spell!!");
}

Spell::~Spell()
{
    debug("destroy a spell");
}

bool Spell::dispell(std::string s) {
    return s == this->a;
}

EnchantedRoom::EnchantedRoom(int n, std::unique_ptr<Spell> s)
    : Room(n),
      _spell(std::move(s))
{
    debug("Creating enchanted room");
}

EnchantedRoom::~EnchantedRoom()
{
    debug("Destroying enchanted Room %d", this->GetRoomNo());
}

void EnchantedRoom::enter(MazePlayer& player) {
    if(_spell->dispell("test"))
    {
        player.setLocation(this->GetRoomNo());
        std::string s = "EnchantedRoom:";
        s += std::to_string(this->GetRoomNo());
        player.status(s);
    }
    else{
        std::string s = "Spell not broken!! location";
        s += std::to_string(this->GetRoomNo());
        player.status(s);
    }
}


Bomb::Bomb(int n)
    :_time(n)
{
    debug("Creating Bomb!! time: %d", this->_time);
}

/*!
 * \brief Bomb destructor
 */
Bomb::~Bomb()
{
    debug("Destroying Bomb!!");
}

int Bomb::GetDetonationTime()
{
    return _time;
}


RoomWithABomb::RoomWithABomb(int n, std::unique_ptr<Bomb> b)
    : Room(n),
      _bomb(std::move(b))
{
    debug("Creating Room with a bomb!!, %d", this->GetRoomNo());
}

RoomWithABomb::~RoomWithABomb()
{
    debug("Destroying Room with a bomb!!");
}

void RoomWithABomb::enter(MazePlayer& player)
{
    player.setLocation(this->GetRoomNo());
    std::string s = "BombedRoom:";
    s += std::to_string(this->GetRoomNo());
    s += " detonation " + std::to_string(_bomb->GetDetonationTime());
    player.status(s);
}

BombedWall::BombedWall()
{
    debug("Creating bombed Wall");
}

BombedWall::~BombedWall()
{
    debug("Destroying bombed Wall");
}

void BombedWall::enter(MazePlayer& player)
{
    player.status("BombedWall");
}

int MazePlayer::getLocation() const
{
    return location;
}

void MazePlayer::setLocation(int value)
{
    location = value;
}

MazePlayer::~MazePlayer()
{

}

MazePlayer::MazePlayer()
    :location(0)
{

}

MazePlayer::MazePlayer(const MazePlayer &other) = default;
MazePlayer& MazePlayer::operator=(const MazePlayer &other) = default;

void MazeTestPlayer::status(std::string s)
{
    _status.clear();
    _status = s;
}

MazeGame::MazeGame()
    :_maze(nullptr)
{
    debug("Creating MazeGame");
}

MazeGame::MazeGame(MazeGame&& rhs) = default;
MazeGame& MazeGame::operator=(MazeGame&& rhs) = default;

MazeGame::~MazeGame()
{
    debug("destroying MazeGame");
}

void MazeGame::CreateMaze()
{
    _maze = std::make_unique<Maze>();

    auto r1 = std::make_shared<Room>(1);
    auto r2 = std::make_shared<Room>(2);

    auto theDoor = std::make_shared<Door>(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    auto w = std::make_shared<Wall>();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);

}

void MazeGame::CreateMaze(MazeFactory* mf)
{
    _maze = mf->MakeMaze();
    std::shared_ptr<Room> r1 = mf->MakeRoom(1);
    std::shared_ptr<Room> r2 = mf->MakeRoom(2);

    std::shared_ptr<Door> theDoor = mf->MakeDoor(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    std::shared_ptr<Wall> w = mf->MakeWall();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);
}

void MazeGame::CreateMaze(std::ostream& out, std::shared_ptr<MazeBuilder> mb)
{
    mb->BuildMaze();
    mb->BuildRoom(1);
    mb->BuildRoom(2);
    mb->BuildDoor(1,2);

    _maze = mb->GetMaze();

    auto cmb = std::dynamic_pointer_cast<CountingMazeBuilder>(mb);
    if(cmb != nullptr)
    {
        int rooms = 0 , doors = 0;
        cmb->GetCounts(rooms, doors);
        out << "room count " << rooms << " door count " << doors;
    }
}


///\{
/*!
 * \brief MazeGame::MakeMaze create a maze
 * \return pointer to maze
 */
std::unique_ptr<Maze> MazeGame::MakeMaze() const
{
    return std::make_unique<Maze>();
}

/*!
 * \brief MazeGame::MakeRoom create a room
 * \param rno
 * \return pointer to room
 */
std::unique_ptr<Room> MazeGame::MakeRoom(int rno) const
{
    return std::make_unique<Room>(rno);
}

/*!
 * \brief MazeGame::MakeDoor create a door
 * \param r1
 * \param r2
 * \return pointer to door
 */
std::unique_ptr<Door> MazeGame::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
    return std::make_unique<Door>(r1, r2);
}

/*!
 * \brief MazeGame::MakeWall create a wall
 * \return pointer to wall
 */
std::unique_ptr<Wall> MazeGame::MakeWall() const
{
    return std::make_unique<Wall>();
}

void MazeGame::CreateMazebyFactoryMethods()
{
    _maze = MakeMaze();

    std::shared_ptr<Room> r1 = MakeRoom(1);
    std::shared_ptr<Room> r2 = MakeRoom(2);

    std::shared_ptr<Door> theDoor = MakeDoor(r1, r2);

    try {
        _maze->AddRoom(r1);
        _maze->AddRoom(r2);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::shared_ptr<Wall> w = MakeWall();

    r1->SetSide(Direction::North, w);
    r1->SetSide(Direction::East, theDoor);
    r1->SetSide(Direction::South, w);
    r1->SetSide(Direction::West, w);

    r2->SetSide(Direction::North, w);
    r2->SetSide(Direction::East, w);
    r2->SetSide(Direction::South, w);
    r2->SetSide(Direction::West, theDoor);
}

BombedMazeGame::BombedMazeGame()
    : MazeGame ()
{
    debug("Creating Bombed Maze Game");
}

BombedMazeGame::~BombedMazeGame()
{
    debug("Destroying Bombed Maze Game");
}

std::unique_ptr<Room> BombedMazeGame::MakeRoom(int rno) const
{
    return std::make_unique<RoomWithABomb>(rno, std::make_unique<Bomb>(rno));
}
std::unique_ptr<Wall> BombedMazeGame::MakeWall() const
{
    return std::make_unique<BombedWall>();
}

EnchantedMazeGame::EnchantedMazeGame()
{
    debug("Creating Enchanted Maze Game");
}
EnchantedMazeGame::~EnchantedMazeGame()
{
    debug("Destroying Enchanted Maze Game");
}

std::unique_ptr<Room> EnchantedMazeGame::MakeRoom(int rno) const
{
    return std::make_unique<EnchantedRoom>(rno, CastSpell());
}

std::unique_ptr<Spell> EnchantedMazeGame::CastSpell() const
{
    return std::make_unique<Spell>("qwe","test");
}

void MazeGame::initGame(MazePlayer &player)
{
    player.setLocation(1);
    _maze->RoomNo(1)->enter(player);
}

void MazeGame::playGame(MazePlayer &player, Direction d)
{
    _maze->RoomNo(player.getLocation())
            ->GetSide(d)
            ->enter(player);
}

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

MazeBuilder::MazeBuilder()
{
    debug("Creating Maze Builder");
}

MazeBuilder::~MazeBuilder()
{
    debug("Destroying Maze Builder");
}

StandardMazeBuilder::StandardMazeBuilder()
    :MazeBuilder (),
      _maze(nullptr)
{
    debug("Creating Standard Maze builder");
}

StandardMazeBuilder::~StandardMazeBuilder()
{
    debug("Destroying Standard Maze Builder");
}

void StandardMazeBuilder::BuildMaze()
{
    _maze = std::make_unique<Maze>();
}

std::unique_ptr<Maze> StandardMazeBuilder::GetMaze()
{
    return std::move(_maze);
}

void StandardMazeBuilder::BuildRoom(int rno)
{
    try {
        _maze->RoomNo(rno);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        auto r = std::make_shared<Room>(rno);
        _maze->AddRoom(r);
        auto w = std::make_shared<Wall>();
        r->SetSide(Direction::East, w);
        r->SetSide(Direction::West, w);
        r->SetSide(Direction::North, w);
        r->SetSide(Direction::South, w);
    }
}

void StandardMazeBuilder::BuildDoor(int r1, int r2)
{
    auto room1 = _maze->RoomNo(r1);
    auto room2 = _maze->RoomNo(r2);
    auto d = std::make_shared<Door>(room1, room2);
    room1->SetSide(CommonWall(room1, room2), d);
    room2->SetSide(CommonWall(room2, room1), d);
}

Direction StandardMazeBuilder::CommonWall(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    if(r1->GetRoomNo() == 1) return Direction::East;
    else return Direction::West;
}

CountingMazeBuilder::CountingMazeBuilder()
    :_rooms(0),
      _doors(0)
{
    debug("Creating Counting Maze Builder");
}

CountingMazeBuilder::~CountingMazeBuilder()
{
    debug("Destroying Counting Maze Builder");
}

void CountingMazeBuilder::BuildMaze()
{
}

std::unique_ptr<Maze> CountingMazeBuilder::GetMaze()
{
    return nullptr;
}


void CountingMazeBuilder::BuildRoom(int rno)
{
    _rooms++;
}

void CountingMazeBuilder::BuildDoor(int r1, int r2)
{
    _doors++;
}

void CountingMazeBuilder::GetCounts(int& rooms, int& doors) const
{
    rooms = _rooms;
    doors = _doors;
}

}
