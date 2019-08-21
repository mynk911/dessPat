#include <boost/geometry.hpp>

#include "foundation.h"
#include "dbg.h"

namespace gof {
namespace bg = boost::geometry;

struct Point::pImpl {
    bg::model::point<double, 2, bg::cs::cartesian> point;
    pImpl(double x, double y) : point(x, y) {
        debug("create pImpl -> boost::geometry::model::point");
    }
};

Point::Point(double x, double y)
    : pimpl(std::make_unique<pImpl>(x, y))
{
    debug("making a point");
}

Point::~Point()
{
    debug("deleting a point");
}

Point& Point::operator=(const Point& other)
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

}
