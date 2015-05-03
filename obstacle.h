#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainter>

#include "obstacleinfo.h"
#include "gameinfo.h"
#include "renderableobject.h"

class Obstacle : public RenderableObject
{
public:
    Obstacle(obstacleInfo obstacle_info, gameInfo *game_info);

    virtual int getY() const;
    int getSpacing() const;
    virtual int getX() const;
    virtual void setSpacing(int spacing);
    void setX(int x);
    virtual void draw(QPainter &painter, bool collision) = 0;
    virtual void updatePosition() = 0;

protected:
    int m_y;
    int m_x;
    int m_spacing;
    int m_speed;
    gameInfo * m_game_info;

};

#endif // OBSTACLE_H
