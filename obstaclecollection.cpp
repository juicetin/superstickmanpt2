#include "obstaclecollection.h"

#include <cstdio>

ObstacleCollection::ObstacleCollection(std::vector<std::map<std::string, int > > obstacles_vector,
                                       int obstacle_speed, int width) : m_speed(obstacle_speed), m_width(width)
{
	for (int i = 0; i < obstacles_vector.size(); ++i)
	{
        m_obstacles.push_back(new ObstacleRectangle(
            obstacles_vector[i]["start-y"], obstacles_vector[i]["spacing"],
                obstacles_vector[i]["height"], obstacles_vector[i]["width"]));
	}

    m_obstacle_loop_length = 0;
    m_obstacles[0]->setX(m_width);
    int vector_length = m_obstacles.size();
    for (int i = 1; i < vector_length; ++i)
    {
        int prev_spacing = m_obstacles[i-1]->getSpacing();
        m_obstacles[i]->setX(m_obstacles[i-1]->getX() + prev_spacing);
        m_obstacle_loop_length += prev_spacing;
    }
}

void ObstacleCollection::renderObstacles(bool update_flag, QPainter &painter, bool animated)
{
    if (animated && update_flag)
	{
//        *update_flag = false;
		for (int i = 0; i < m_obstacles.size(); ++i)
		{
			painter.drawRect(QRect(m_obstacles[i]->getX(), m_obstacles[i]->getY(),
				static_cast<ObstacleRectangle*>(m_obstacles[i])->getWidth(),
				static_cast<ObstacleRectangle*>(m_obstacles[i])->getHeight()));

            int current_x = m_obstacles[i]->getX();

            //Loop when the entire length of the object has passed the left of the screen
            if (current_x + static_cast<ObstacleRectangle*>(m_obstacles[i])->getWidth() < 0) {
                m_obstacles[i]->setX(current_x + m_obstacle_loop_length + m_width);
			}
			else
			{
            	m_obstacles[i]->setX(current_x-m_speed);
			}
		}
	}
}

ObstacleCollection::~ObstacleCollection()
{
	for (int i = 0; i < m_obstacles.size(); ++i)
	{
		delete m_obstacles[i];
	}
}
