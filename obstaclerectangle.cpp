#include "obstaclerectangle.h"

ObstacleRectangle::ObstacleRectangle(obstacleInfo obstacle_info, gameInfo *game_info) : 
Obstacle(obstacle_info, game_info),
m_height(obstacle_info.height), m_width(obstacle_info.width)
{
    m_fall = true;
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

//    if (m_fall && m_y + m_height < (*m_game_info).y_dimension)
//    {
//        m_y += 1;
//    }
//    else if (m_fall && m_y + m_height == (*m_game_info).y_dimension)
//    {
//        m_fall = false;
//    }
//    else if (!m_fall && m_y > 0)
//    {
//        m_y -= 1;
//    }
//    else if (!m_fall && m_y == 0)
//    {
//        m_fall = true;
//    }
}

void ObstacleRectangle::draw(QPainter &painter, bool collision)
{
    //This draws objects outside the window too!

    painter.setPen(QColor(m_obstacle_info.color.c_str()));
    QBrush brush(QColor((m_obstacle_info.color.c_str())));
    QRect rect(QRect(m_x, m_y, m_width, m_height));
    painter.drawRect(rect);
    painter.fillRect(rect, brush);
	if (!collision)
	{
		updatePosition();
	}
}
