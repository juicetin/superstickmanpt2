#ifndef RENDERABLEOBJECT
#define RENDERABLEOBJECT

#include <QPainter>

class RenderableObject
{
public:
    virtual void draw(QPainter &painter, bool collision) = 0;
};

#endif // RENDERABLEOBJECT

