#ifndef GOF_DECORATOR_H_
#define GOF_DECORATOR_H_

#include "gof_export.h"

namespace  gof {
class GOF_EXPORT VisualComponent
{
public:
    virtual void Draw() = 0;
    virtual void Resize() = 0;
protected:
    VisualComponent();
    virtual ~VisualComponent();
};

class GOF_EXPORT TextV : public VisualComponent
{
public:
    TextV();

    // VisualComponent interface
public:
    void Draw() override;
    void Resize() override;
};

class GOF_EXPORT Decorator : public VisualComponent
{
public:
    virtual void Draw();
    virtual void Resize();
protected:
    Decorator(VisualComponent*);
    virtual ~Decorator();
private:
    VisualComponent* _component;
};

class GOF_EXPORT BorderDecorator : public Decorator
{
public:
    BorderDecorator(VisualComponent*, int borderWidth);
    ~BorderDecorator() override;
    void Draw() override;
private:
    void DrawBorder(int);
    int _width;
};

class GOF_EXPORT ScrollDecorator : public Decorator
{
public:
    ScrollDecorator(VisualComponent*);
    ~ScrollDecorator() override;
    void Draw() override;
    void Resize() override;
private:
    void DrawScroll();
    void ResizeScroll();
};

class GOF_EXPORT DropShadowDecorator : public Decorator
{
public:
    DropShadowDecorator(VisualComponent*, int depth);
    ~DropShadowDecorator() override;
    void Draw() override;
private:
    void DrawShadow(int);
    int _depth;
};

class GOF_EXPORT Window
{
public:
    Window();
    ~Window();
    void SetContents(VisualComponent*);
private:
    VisualComponent* _contents;
};
}
#endif
