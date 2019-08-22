#ifndef GOF_COMPOSITE_H_
#define GOF_COMPOSITE_H_

#include <list>
#include <functional>

#include "gof_export.h"

namespace gof {
typedef double Currency;
class Equipment;
class List;
class GOF_EXPORT Equipment
{
public:
    virtual ~Equipment();

    const char* Name() {return _name;}

    virtual Currency NetPrice() = 0;

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    bool operator==(Equipment& other) { return _name == other._name;}
protected:
    Equipment(const char*);
private:
    const char* _name;
};

class GOF_EXPORT FloppyDisk : public Equipment
{
public:
    FloppyDisk(const char* name) :Equipment(name) {}
    ~FloppyDisk() override;

    Currency NetPrice()  override { return 5.0; }
};

class GOF_EXPORT Card : public Equipment
{
public:
    Card(const char* name) :Equipment(name) {}
    ~Card() override;

    Currency NetPrice() override { return 15.0; }
};

class GOF_EXPORT CompositeEquipment : public Equipment
{
public:
    virtual ~CompositeEquipment();

    Currency NetPrice();

    void Add(Equipment*);
    void Remove(Equipment*);
protected:
    CompositeEquipment(const char* name) :Equipment(name) {}
private:
    std::list<std::reference_wrapper<Equipment>> _equipment;
};

class GOF_EXPORT Chassis : public CompositeEquipment
{
public:
    Chassis(const char* name) :CompositeEquipment(name) {}
    ~Chassis() override;

    Currency NetPrice() override { return 5 + CompositeEquipment::NetPrice();}
};

class GOF_EXPORT Cabinet : public CompositeEquipment
{
public:
    Cabinet(const char* name) :CompositeEquipment(name) {}
    ~Cabinet() override;

    Currency NetPrice() override { return 10 + CompositeEquipment::NetPrice();}
};

class GOF_EXPORT Bus : public CompositeEquipment
{
public:
    Bus(const char* name) :CompositeEquipment(name) {}
    ~Bus() override;

    Currency NetPrice() override { return 2 + CompositeEquipment::NetPrice();}
};
}
#endif //GOF_COMPOSITE_H_
