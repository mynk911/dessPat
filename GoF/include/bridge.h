#ifndef GOF_BRIDGE_H_
#define GOF_BRIDGE_H_

#include "gof_export.h"

namespace gof {

/* Design of a Window WindowImp Design system. Window let's us create windows of different
/ types independent of implementation. The file currently contains empty design of top level
/ classes. For a concrete example,
1) Need to gain knowledge of at least one window display framework such as X or native windows
from both implementation point of view as well as how to fit it in the design
*/
class View;
class Point;
class WindowImp;

class Window {
public:
    Window(View* contents);
    virtual ~Window();
    Window(Window&);
    Window(Window&&) = default;
    Window& operator=(Window&);
    Window& operator=(Window&&) = default;
    // these requests may use windowImp. Thier implementation differs
    // different child classes
    /// requests handled by window
    /// @{
    virtual void drawContents() = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual void Iconify() = 0;
    virtual void Deiconify() = 0;
    //...
    /// @}
    // these requests usually are forwarded to imp as is.
    /// requests forwarded to implementation
    /// @{
    virtual void SetOrigin(const Point& at);
    virtual void SetExtent(const Point& extent);
    virtual void Raise();
    virtual void Lower();
    virtual void DrawLine(const Point&, const Point&);
    virtual void DrawRect(const Point&, const Point&);
    virtual void DrawPolygon(const Point[], int n);
    virtual void DrawText(const char*, const Point&);
    //...
    /// @}

protected:
    WindowImp* GetWindowImp();
    View* GetView();

private:
    WindowImp* _imp;
    View* contents;
};

// inherited by application window, ico  window etc
// an abstract factory for obtaining right windowImp

}
#endif
