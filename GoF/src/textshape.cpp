#include "textshape.h"
#include "dbg.h"

namespace gof {
namespace structural {

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
TextShape::TextShape(double left, double bottom, double right, double top)
    :Shape(left, bottom, right, top),
      Textview (left, bottom, right - left, top - bottom)
{
    debug("Creating TextShape");
}

TextShape::~TextShape()
{
    debug("destroying TextShape");
}

void TextShape::BoundingBox(Point *bottomLeft, Point *topRight) const
{
    Coord bottom, left, width, height;
    GetOrigin(bottom, left);
    GetExtent(width, height);
    *bottomLeft = Point(bottom, left);
    *topRight = Point(bottom + height, left + width);
}

bool TextShape::IsEmpty() const
{
    return Textview::IsEmpty();
}

std::unique_ptr<Manipulator> TextShape::CreateManipulator() const
{
    return std::make_unique<TextManipulator>(*this);
}

}}
