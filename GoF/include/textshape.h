#ifndef TEXT_SHAPE_H_
#define TEXT_SHAPE_H_

#include "shape.h"
#include "textview.h"
#include "gof_export.h"

namespace gof {

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

#endif
