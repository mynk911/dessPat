#ifndef _TEXT_SHAPE_H_
#define _TEXT_SHAPE_H_

#include "shape.h"
#include "textview.h"
class TextShape;
class TextManipulator : public Manipulator
{
public:
    TextManipulator(const TextShape& txtshape);
    ~TextManipulator();
    void manipulate() override;
};
class TextShape : public Shape, private Textview
{
public:
    TextShape();
    ~TextShape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const override;
    virtual bool IsEmpty() const override;
    virtual Manipulator* CreateManipulator() const override;
};

#endif