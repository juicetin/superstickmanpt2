#include "obstaclerectangle.h"

ObstacleRectangle::ObstacleRectangle(obstacleInfo obstacle_info, gameInfo *game_info) : 
Obstacle(obstacle_info, game_info),
m_height(obstacle_info.height), m_width(obstacle_info.width)
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

void ObstacleRectangle::updatePosition()
{
	if (m_x + m_width < 0)
	{
		m_x += m_game_info->obstacle_loop_length + m_game_info->x_dimension;
	}
	else
	{
		m_x -= m_game_info->obstacle_speed;
	}	
}

void ObstacleRectangle::draw(QPainter &painter, bool collision)
{
    //This draws objects outside the window too!
	painter.drawRect(QRect(m_x, m_y, m_width, m_height));
	if (!collision)
	{
		updatePosition();
	}
}
