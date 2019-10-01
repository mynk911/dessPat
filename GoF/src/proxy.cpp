#include <string.h>
#include "proxy.h"

namespace gof {

Image::Image(const char* file)
{
    // loads image from a file
}
Image::~Image() {}
void Image::Draw(const Point& at) {}
void Image::HandleMouse(Event& event)
{
    // handle resizing
}
const Point& Image::GetExtent() { return Point(2, 3); }
void Image::Load(std::istream& from) {}
void Image::Save(std::ostream& to) {}

ImageProxy::ImageProxy(const char* imageFile)
    : _extent(0, 0)
{
    _fileName = strdup(imageFile);
    // don't know extent yet
    _image = 0;
}
ImageProxy::~ImageProxy() {}

Image* ImageProxy::GetImage() {
    if (_image == 0) {
	_image = new Image(_fileName);
    }
    return _image;
}

void ImageProxy::Draw(const Point& at)
{
    GetImage()->Draw(at);
}
void ImageProxy::HandleMouse(Event& event)
{
    GetImage()->HandleMouse(event);
}
const Point& ImageProxy::GetExtent()
{
    if (_extent.getX() == 0 && _extent.getY() == 0) {
	_extent = GetImage()->GetExtent();
    }
    return _extent;
}
void ImageProxy::Load(std::istream& from)
{
    int x, y;
    from >> x >> y >> _fileName;
    Point p(x, y);
    _extent = p;
}
void ImageProxy::Save(std::ostream& to)
{
    to << _extent.getX() << _extent.getY() << _fileName;
}

}
