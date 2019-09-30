#ifndef GOF_PROXY_H_
#define GOF_PROXY_H_

#include "foundation.h"
#include <istream>
#include <ostream>

namespace gof {
class Event;
// Graphic abstract base
class Graphic {
public:
    virtual ~Graphic() {};
    virtual void Draw(const Point& at) = 0;
    virtual void HandleMouse(Event& event) = 0;
    virtual const Point& GetExtent() = 0;
    virtual void Load(std::istream& from) = 0;
    virtual void Save(std::ostream& to) = 0;
protected:
    Graphic() {};
};

// data heavy image class
class Image : public Graphic {
public:
    Image(const char* file); // loads image from a file
    virtual ~Image();
    virtual void Draw(const Point& at);
    virtual void HandleMouse(Event& event);
    virtual const Point& GetExtent();
    virtual void Load(std::istream& from);
    virtual void Save(std::ostream& to);
private:
    // ...
};

class ImageProxy : public Graphic {
public:
    ImageProxy(const char* imageFile);
    virtual ~ImageProxy();
    virtual void Draw(const Point& at);
    virtual void HandleMouse(Event& event);
    virtual const Point& GetExtent();
    virtual void Load(std::istream& from);
    virtual void Save(std::ostream& to);
protected:
    Image* GetImage();
private:
    Image* _image;
    Point _extent;
    char* _fileName;
};

}
#endif // GOF_PROXY_H_