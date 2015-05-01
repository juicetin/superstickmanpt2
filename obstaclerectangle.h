#ifndef OBSTACLERECTANGLE_H
#define OBSTACLERECTANGLE_H

#include "obstacle.h"

class ObstacleRectangle : public Obstacle
{
public:
    ObstacleRectangle(int y, int spacing, int m_height, int m_width);
    int getHeight() const;
    int getWidth() const;

protected:
	int m_height;
	int m_width;
};

#endif // OBSTACLERECTANGLE_H
