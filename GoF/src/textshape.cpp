#include "textshape.h"
#include "dbg.h"

TextManipulator::TextManipulator(const TextShape& txtShape)
    : Manipulator(txtShape)
{
    debug("Creating a text manipulator");
}

TextManipulator::~TextManipulator()
{
    debug("destroying a text manipulator");
}

void TextManipulator::manipulate()
{

}
TextShape::TextShape()
{
    debug("Creating TextShape");
}

TextShape::~TextShape()
{
    debug("destroying TextShape");
}

void TextShape::BoundingBox(Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;
    GetOrigin(bottom, left);
    GetExtent(width, height);
    Point p1(bottom, left);
    bottomLeft = p1;
    Point p2(bottom + height, left + width);
    topRight = p2;
}

bool TextShape::IsEmpty() const
{
    return Textview::IsEmpty();
}

Manipulator* TextShape::CreateManipulator() const
{
    return new TextManipulator(*this);
}
