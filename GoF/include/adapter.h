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

/** Adaptee becomes implementation detail in Adapter.
 * TextView holds a bouding box represented by bottom left corner, height
 * and width. Origin assumed at bottom left corner of screen.
 * @ingroup Adapter
 */
class GOF_EXPORT TextView
{
public:
    /// accepts four Coord values and define bounding box.
    TextView(Coord OriginX, Coord OriginY, Coord width, Coord height);
    /// destructor
    virtual ~TextView();
    /** Get Origin
     * @param x[out] horizontal distance of bottom-left corner from origin.
     * @param y[out] vertical  distance of bottom-left corner from origin.
     */
    void GetOrigin(Coord& x, Coord& y) const;
    /** Get Extent
     * @param width[out] horizontal distance of top-right corner from bottom-left.
     * @param height[out] vertical distance of top-right corner from bottom-left.
     */
    void GetExtent(Coord& width,Coord& height) const;
    /// checks if this object is empty.
    virtual bool IsEmpty() const;
private:
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
};

class TextShape;

/// Manipulator for the TextShape object.
class GOF_EXPORT TextManipulator : public Manipulator
{
public:
    /// constructor
    TextManipulator(const TextShape& txtshape);
    /// destructor
    ~TextManipulator() override;
    void manipulate() override;
};

/** Adapter : encapsulates TextView and implements Shape.
 * @ingroup Adapter
 */
class GOF_EXPORT TextShape : public Shape, private TextView
{
public:
    /// @copydoc gof::Shape::Shape
    TextShape(double left, double bottom, double right, double top);
    /// destructor.
    ~TextShape() override;
    virtual void BoundingBox(Point* bottomLeft, Point* topRight) const override;
    virtual bool IsEmpty() const override;
    virtual std::unique_ptr<Manipulator> CreateManipulator() const override;
};

}

#endif /*  */
