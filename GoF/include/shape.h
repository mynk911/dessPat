#ifndef _GOF_SHAPE_H_
#define _GOF_SHAPE_H_

#include <memory>
class Shape;
class Point
{
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
public:
    Point(double x, double y);
    virtual ~Point();
    Point& operator=(Point& other);
    void set(double x, double y);
    double getX();
    double getY();
};

class Manipulator {
    const Shape& shp;
public:
    Manipulator(const Shape& shape);
    virtual ~Manipulator();
    virtual void manipulate();
};

class Shape
{
private:


public:
    Shape();
    virtual ~Shape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* CreateManipulator() const;
};

#endif /*  */
