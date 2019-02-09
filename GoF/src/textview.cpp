#include "dbg.h"
#include "textview.h"

class Coord
{
    double x;
    double y;
    void setPoint(double a, double b)
    {
        x = a;
        y = b;
    }
    double getX() const { return x;}
    double getY() const { return y;}
};

Textview::Textview()
{
    debug("creating textview");
}

Textview::~Textview()
{
    debug("destroying textview");
}

void Textview::GetOrigin(Coord& x, Coord& y) const
{

}

void Textview::GetExtent(Coord& width, Coord& height) const
{

}

bool Textview::IsEmpty() const
{
    return false;
}
