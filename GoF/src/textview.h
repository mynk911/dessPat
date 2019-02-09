#ifndef _GOF_TEXTVIEW_H_
#define _GOF_TEXTVIEW_H_

class Coord;
class Textview 
{
    Textview();
    ~Textview();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width,Coord& height) const;
    virtual bool IsEmpty() const;
};
#endif
