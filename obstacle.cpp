#include "obstacle.h"

Obstacle::Obstacle()
{

}

int Obstacle::setStartY(int start_y)
{
	m_start_y = start_y;
}
int Obstacle::getStartY() const
{
    return m_start_y;
}

int Obstacle::setHeight(int height)
{
    m_height = height;
}
int Obstacle::getHeight() const
{
    return m_height;
}

int Obstacle::setWidth(int width)
{
    m_width = width;
}
int Obstacle::getWidth() const
{
    return m_width;
}

int Obstacle::setSpacing(int spacing)
{
    m_spacing = spacing;
}
int Obstacle::getSpacing() const
{
    return m_spacing;
}


