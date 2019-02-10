#ifndef _GOF_TEXTVIEW_H_
#define _GOF_TEXTVIEW_H_

#include <memory>

using Coord = double;

class Textview
{
public:
    Textview();
    virtual ~Textview();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width,Coord& height) const;
    virtual bool IsEmpty() const;
private:
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
};
#endif
