#ifndef GOF_FLYWEIGHT_H_
#define GOF_FLYWEIGHT_H_

namespace gof {
// Since there is an abundance of window display examples. It would be better to build one
// example incorporating all related patterns
class GlyphContext;
class Window;
class Font;
class Row;
class Column;

// maintains what range of characters have what font
class BTree;

// Composite base class
class Glyph
{
public:
    virtual ~Glyph()
    {
    }
    // GlyphContext objects pass extrinsinc info for flyweight objects
    virtual void Draw(Window*, GlyphContext&);
    virtual void SetFont(Font*, GlyphContext&);
    virtual Font* GetFont(GlyphContext&);

    // Iteration and Child management
    virtual void First();
    virtual void Next();
    virtual void IsDone();
    virtual Glyph* Current(GlyphContext&);
    virtual void Insert(Glyph*, GlyphContext&);
    virtual void Remove(GlyphContext&);

protected:
    Glyph()
    {
    }
private:

};

class Character : public Glyph
{
    Character(char);
    virtual void Draw(Window*, GlyphContext&) override;
private:
    char _charcode;
};

class GlyphContext {
public:
    GlyphContext() {}
    virtual ~GlyphContext() {}
    virtual void Next(int);
    virtual void Insert(int);
    virtual void GetFont();
    virtual void SetFont(Font, int span);
private:
    int _index;
    BTree* _fonts;
};

const int NCHARCODES = 128;
class GlyphFactory {
public:
    GlyphFactory();
    virtual ~GlyphFactory();
    virtual Character* CreateCharacter(char);
    virtual Row* CreateRow();
    virtual Column* CreateColumn();
    // ...
private:
    Character* _character[NCHARCODES];
};

}
#endif // GOF_FLYWEIGHT_H_