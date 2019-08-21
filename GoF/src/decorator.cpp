#include "decorator.h"

namespace gof {
VisualComponent::VisualComponent() {}

VisualComponent::~VisualComponent() {}

void Decorator::Draw()
{
    _component->Draw();
}

void Decorator::Resize()
{
    _component->Resize();
}

Decorator::Decorator(VisualComponent *comp)
    :_component(comp)
{}

Decorator::~Decorator() {}

BorderDecorator::BorderDecorator(VisualComponent *vc, int borderWidth)
    :Decorator (vc), _width(borderWidth)
{}

BorderDecorator::~BorderDecorator() {}

void BorderDecorator::Draw()
{
    Decorator::Draw();
    DrawBorder(_width);
}

void BorderDecorator::DrawBorder(int) {}

ScrollDecorator::ScrollDecorator(VisualComponent *vc)
    :Decorator (vc)
{}

ScrollDecorator::~ScrollDecorator() {}

void ScrollDecorator::Draw()
{
    Decorator::Draw();
    DrawScroll();
}

void ScrollDecorator::Resize()
{
    Decorator::Resize();
    ResizeScroll();
}

void ScrollDecorator::DrawScroll() {}
void ScrollDecorator::ResizeScroll() {}

DropShadowDecorator::DropShadowDecorator(VisualComponent *vc, int depth)
    :Decorator (vc), _depth(depth)
{}

DropShadowDecorator::~DropShadowDecorator() {}

void DropShadowDecorator::Draw()
{
    Decorator::Draw();
    DrawShadow(_depth);
}

void DropShadowDecorator::DrawShadow(int) {}

Window::Window()
    :_contents(nullptr)
{}

Window::~Window() {}

void Window::SetContents(VisualComponent* contents)
{
    _contents = contents;
}

TextV::TextV() {}

void TextV::Draw()
{
}

void TextV::Resize()
{
}

}
