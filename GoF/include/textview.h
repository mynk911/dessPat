#ifndef _GOF_TEXTVIEW_H_
#define _GOF_TEXTVIEW_H_

#include <memory>
#include "gof_export.h"

namespace gof {
namespace structural {

using Coord = double;

class GOF_EXPORT Textview
{
public:
    Textview(Coord OriginX, Coord OriginY, Coord width, Coord height);
    virtual ~Textview();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width,Coord& height) const;
    virtual bool IsEmpty() const;
private:
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
};

}}

#endif
