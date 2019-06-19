#include "dbg.h"
#include "textview.h"

namespace gof {

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

}

