#include <boost/geometry.hpp>

namespace bg = boost::geometry;

#include "dbg.h"
#include "shape.h"

class Point 
{
    bg::model::point<double, 2, bg::cs::cartesian> point;
 public:
    void set(double x, double y)
    {
        point.set<0>(x);
        point.set<1>(y);
    }
    double getX()
    {
        return point.get<0>();
    }
    double getY()
    {
        return point.get<1>();
    }
};

class Manipulator{
    int a;
};
Shape::Shape()
{
    debug("creating shape");
}

Shape::~Shape()
{
    debug("destroying shape");
}

void Shape::BoundingBox(Point& bottomLeft, Point& topRight) const
{

}

Manipulator* Shape::CreateManipulator() const
{
    return new Manipulator;
}
