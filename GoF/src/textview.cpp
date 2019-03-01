#include "dbg.h"
#include "textview.h"

namespace gof {
namespace structural {

struct Textview::pImpl {
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

Textview::Textview(Coord OriginX, Coord OriginY, Coord width, Coord height)
    : pimpl(std::make_unique<pImpl>(OriginX, OriginY, width, height))
{
    debug("creating textview");
}

Textview::~Textview()
{
    debug("destroying textview");
}

void Textview::GetOrigin(Coord& x, Coord& y) const
{
    x = pimpl->OriginX;
    y = pimpl->OriginY;
}

void Textview::GetExtent(Coord& width, Coord& height) const
{
    width = pimpl->width;
    height = pimpl->height;
}

bool Textview::IsEmpty() const
{
    return false;
}

}}

