#ifndef _GOF_SHAPE_H_
#define _GOF_SHAPE_H_

#include <memory>
#include "gof_export.h"

namespace gof {
namespace structural {

class Shape;
class GOF_EXPORT Point
{
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
public:
    Point(double x, double y);
    virtual ~Point();
    Point& operator=(const Point& other);
    void set(double x, double y);
    double getX();
    double getY();
};

class GOF_EXPORT Manipulator {
    const Shape& shp;
public:
    Manipulator(const Shape& shape);
    virtual ~Manipulator();
    virtual void manipulate();
};

class GOF_EXPORT Shape
{
private:
    Point bLeft;
    Point tRight;
public:
    Shape(double left, double bottom, double right, double top);
    virtual ~Shape();
    virtual void BoundingBox(Point* bottomLeft, Point* topRight) const;
    virtual std::unique_ptr<Manipulator> CreateManipulator() const;
};

}}

#endif /*  */
