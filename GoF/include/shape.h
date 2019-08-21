#ifndef _GOF_SHAPE_H_
#define _GOF_SHAPE_H_

#include <memory>
#include "gof_export.h"
#include "foundation.h"

namespace gof {

class Shape;

/// takes a shape object and peerforms a generic action on it.
class GOF_EXPORT Manipulator {
    const Shape& shp;
public:
    /// constructor.
    Manipulator(const Shape& shape);
    /// destructor.
    virtual ~Manipulator();
    /// generic action.
    virtual void manipulate();
};

/** Target class whose interface the adapter TextShape implements.
 * Shape holds a rectangular bounding box defined by two end points of right
 * diagonal. Bottom left of screen is assumed to be origin.
 * @ingroup Adapter
 */
class GOF_EXPORT Shape
{
private:
    Point bLeft;
    Point tRight;
public:
    /// accepts four double values and defines bounding box of shape
    Shape(double left, double bottom, double right, double top);
    /// destructor
    virtual ~Shape();
    /** returns BoundingBox of the given shape.
     * @param bottomLeft[out] Point bottom left corner of bounding box.
     * @param topRight[out] top right corner of bounding box.
     */
    virtual void BoundingBox(Point* bottomLeft, Point* topRight) const;
    /// Factory method for creating Manipulator.
    virtual std::unique_ptr<Manipulator> CreateManipulator() const;
};

}

#endif /*  */
