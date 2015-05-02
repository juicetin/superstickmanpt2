#include "obstacle.h"

Obstacle::Obstacle(obstacleInfo obstacle_info, gameInfo *game_info) :
	m_y(obstacle_info.start_y), m_spacing(obstacle_info.spacing),
    m_speed(obstacle_info.speed), m_game_info(game_info)
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