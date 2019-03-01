#ifndef _TEXT_SHAPE_H_
#define _TEXT_SHAPE_H_

#include "shape.h"
#include "textview.h"
#include "gof_export.h"

namespace gof {
namespace structural {

class TextShape;
class GOF_EXPORT TextManipulator : public Manipulator
{
public:
    TextManipulator(const TextShape& txtshape);
    ~TextManipulator() override;
    void manipulate() override;
};
class GOF_EXPORT TextShape : public Shape, private Textview
{
public:
    TextShape(double left, double bottom, double right, double top);
    ~TextShape() override;
    virtual void BoundingBox(Point* bottomLeft, Point* topRight) const override;
    virtual bool IsEmpty() const override;
    virtual std::unique_ptr<Manipulator> CreateManipulator() const override;
};

}}

#endif
