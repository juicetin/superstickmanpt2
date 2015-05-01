#include "obstacle.h"

Obstacle::Obstacle(int y, int spacing) : m_y(y), m_spacing(spacing)
{

}

int Obstacle::getY() const
{
    return m_y;
}

int Obstacle::getSpacing() const
{
    return m_spacing;
}

int Obstacle::getX() const
{
	return m_x;
}

void Obstacle::setX(int x)
{
	m_x = x;
}