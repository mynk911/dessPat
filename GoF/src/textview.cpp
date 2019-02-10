#include "dbg.h"
#include "textview.h"

struct Textview::pImpl {
    Coord OriginX;
    Coord OriginY;
    Coord width;
    Coord height;
};

Textview::Textview()
    : pimpl(std::move(std::make_unique<pImpl>()))
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
