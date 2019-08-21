#ifndef GOF_FOUNDATION_H_
#define GOF_FOUNDATION_H_

#include "gof_export.h"
#include <memory>

namespace gof {

using Coord = double;

/// represents a point in 2D cartesian plane.
class GOF_EXPORT Point
{
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
public:
    /** Point constructor
     * @param x distance from origin on x axis.
     * @param y distance from origin on y axis.
     */
    Point(double x, double y);
    /// destroy a point.
    virtual ~Point();
    /// makes a deep copy of private data.
    Point& operator=(const Point& other);
    /// sets point to values x and y.
    void set(double x, double y);
    /// get x.
    double getX();
    /// get y.
    double getY();
};
}

#endif
