//NOTE, TO FIX - NO OBSTACLES IN CONFIG CRASHES

#include "obstaclecollection.h"

#include <cstdio>

ObstacleCollection::ObstacleCollection(std::vector<std::map<std::string, int > > obstacles_vector, gameInfo game_info) :
m_speed(game_info.obstacle_speed), m_width(game_info.x_dimension), m_height(game_info.y_dimension),
m_game_info(game_info)
{
	for (int i = 0; i < obstacles_vector.size(); ++i)
    {
        m_obstacles.push_back(ObstacleFactory::create(obstacles_vector[i], &m_game_info));
        if (m_obstacles.back() == NULL)
            m_obstacles.pop_back();
    }

    int obstacle_loop_length = static_cast<ObstacleRectangle*>(m_obstacles[0])->getWidth();
    m_obstacles[0]->setX(m_width);
    int vector_length = m_obstacles.size();
    for (int i = 1; i < vector_length; ++i)
    {
        int prev_spacing = m_obstacles[i-1]->getSpacing();
        int prev_width = static_cast<ObstacleRectangle*>(m_obstacles[i-1])->getWidth();
        m_obstacles[i]->setX(m_obstacles[i-1]->getX() + prev_spacing + prev_width);
        obstacle_loop_length += prev_spacing + prev_width;
    }
    m_obstacles[obstacles_vector.size()-1]->setSpacing(obstacle_loop_length - m_width);
    m_game_info.obstacle_loop_length = obstacle_loop_length;
}

void ObstacleCollection::renderObstacles(bool update_flag, QPainter &painter, bool animated)
{
    if (animated && update_flag)
    {
        for (int i = 0; i < m_obstacles.size(); ++i)
        {
            m_obstacles[i]->draw(painter, *m_collision);
        }
    }
}

std::vector<Obstacle*> * ObstacleCollection::getObstacles()
{
	return &m_obstacles;
}

ObstacleCollection::~ObstacleCollection()
{
	for (int i = 0; i < m_obstacles.size(); ++i)
    {
		delete m_obstacles[i];
	}
}

void ObstacleCollection::setCollision(bool * collision)
{
    m_collision = collision;
}
