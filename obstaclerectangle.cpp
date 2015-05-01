#include "obstaclerectangle.h"

ObstacleRectangle::ObstacleRectangle(int y, int spacing, int height, int width) : Obstacle(y, spacing), m_height(height), m_width(width)
{

}
 
int ObstacleRectangle::getHeight() const
{
	return m_height;
}

int ObstacleRectangle::getWidth() const
{
	return m_width;
}