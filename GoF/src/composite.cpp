#include <exception>
#include <algorithm>

#include "composite.h"

namespace gof {

Equipment::~Equipment()
{

}

void Equipment::Add(Equipment *)
{
    throw std::logic_error("Can only add to composite equipment");
}

void Equipment::Remove(Equipment *)
{
    throw std::logic_error("Can only add to composite equipment");
}

Equipment::Equipment(const char *name)
    :_name(name)
{}

CompositeEquipment::~CompositeEquipment()
{

}

Currency CompositeEquipment::NetPrice()
{
    Currency total = 0;

    for(auto& eq : _equipment)
        total += eq.get().NetPrice();
    return total;
}

void CompositeEquipment::Add(Equipment *equip)
{
    _equipment.push_back(*equip);
}

void CompositeEquipment::Remove(Equipment *equip)
{
    _equipment.erase(std::remove(_equipment.begin(), _equipment.end(), std::ref(*equip)));
}

bool operator==(std::reference_wrapper<Equipment> a, std::reference_wrapper<Equipment> b)
{
    return a.get().operator==(b.get());
}

Bus::~Bus()
{

}

Cabinet::~Cabinet()
{

}

Chassis::~Chassis()
{

}

Card::~Card()
{

}

FloppyDisk::~FloppyDisk()
{

}

}
