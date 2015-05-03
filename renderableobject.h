#ifndef RENDERABLEOBJECT
#define RENDERABLEOBJECT

#include <QPainter>

class RenderableObject
{
public:
    virtual void draw(QPainter &painter, bool update_flag) = 0;
};

#endif // RENDERABLEOBJECT

