#include "dbg.h"
#include "adapter.h"

namespace gof {

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

Shape::Shape(double left, double bottom, double right, double top)
    : bLeft(left, bottom),
      tRight(right, top)
{
    debug("creating shape");
}

Shape::~Shape()
{
    debug("destroying shape");
}

void Shape::BoundingBox(Point *bottomLeft, Point *topRight) const
{
    *bottomLeft = bLeft;
    *topRight = tRight;
}

std::unique_ptr<Manipulator> Shape::CreateManipulator() const
{
    return std::make_unique<Manipulator>(*this);
}

struct TextView::pImpl {
    Coord OriginX;
    Coord OriginY;
    Coord width;
    Coord height;
    pImpl(Coord x, Coord y, Coord w, Coord h) :
        OriginX(x),
        OriginY(y),
        width(w),
        height(h)
    {
        debug("setting coordinates");
    }
};

TextView::TextView(Coord OriginX, Coord OriginY, Coord width, Coord height)
    : pimpl(std::make_unique<pImpl>(OriginX, OriginY, width, height))
{
    debug("creating textview");
}

TextView::~TextView()
{
    debug("destroying textview");
}

void TextView::GetOrigin(Coord& x, Coord& y) const
{
    x = pimpl->OriginX;
    y = pimpl->OriginY;
}

void TextView::GetExtent(Coord& width, Coord& height) const
{
    width = pimpl->width;
    height = pimpl->height;
}

bool TextView::IsEmpty() const
{
    return false;
}

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
      TextView (left, bottom, right - left, top - bottom)
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
    return TextView::IsEmpty();
}

std::unique_ptr<Manipulator> TextShape::CreateManipulator() const
{
    return std::make_unique<TextManipulator>(*this);
}

}

