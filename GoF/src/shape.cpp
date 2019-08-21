#include "dbg.h"
#include "shape.h"

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

}

