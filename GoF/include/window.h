#ifndef GOF_WINDOW_H_
#define GOF_WINDOW_H_

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
    /// requests handled by window
    /// @{
    virtual void drawContents() = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual void Iconify() = 0;
    virtual void Deiconify() = 0;
    /// @}

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
#endif
