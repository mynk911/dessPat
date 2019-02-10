#include <boost/geometry.hpp>

#include "dbg.h"
#include "shape.h"

namespace bg = boost::geometry;

struct Point::pImpl {
    bg::model::point<double, 2, bg::cs::cartesian> point;
};

Point::Point(double x, double y)
    : pimpl(std::move(std::make_unique<pImpl>()))
{
    debug("making a point");
}

Point::~Point()
{
    debug("deleting a point");
}

Point& Point::operator=(Point& other)
{
    *pimpl = *other.pimpl;
    return *this;
}
void Point::set(double x, double y)
{
    pimpl->point.set<0>(x);
    pimpl->point.set<1>(y);
}

double Point::getX()
{
    return pimpl->point.get<0>();
}
double Point::getY()
{
    return pimpl->point.get<1>();
}

Manipulator::Manipulator(const Shape& shape)
    : shp(shape)
{
    debug("creating a manipulator");
}

Manipulator::~Manipulator()
{
    debug("destroying a manipulator");
}

void Manipulator::manipulate()
{

}

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
    return new Manipulator(*this);
}
