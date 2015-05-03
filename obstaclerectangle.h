#ifndef OBSTACLERECTANGLE_H
#define OBSTACLERECTANGLE_H

#include <QBrush>
#include <QColor>
#include "obstacle.h"

class ObstacleRectangle : public Obstacle
{
public:
    ObstacleRectangle(obstacleInfo obstacle_info, gameInfo *game_info);
    int getHeight() const;
    int getWidth() const;
    virtual void draw(QPainter &painter, bool collision);
    virtual void updatePosition();

protected:
	int m_height;
    int m_width;
};

#endif // OBSTACLERECTANGLE_H
