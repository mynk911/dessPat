#ifndef _GOF_SHAPE_H_
#define _GOF_SHAPE_H_

class Point;
class Manipulator;
class Shape
{
private:
    

public:
    Shape();
    virtual ~Shape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* CreateManipulator() const;
};

#endif /*  */
