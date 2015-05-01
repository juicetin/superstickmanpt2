#include "obstaclefactory.h"

ObstacleFactory::ObstacleFactory(std::vector <std::pair<std::string, std::map<std::string, int> > > obstacleVector)
    : m_obstacleVector(obstacleVector)
{
    m_obstacles = new Obstacle[m_obstacleVector.size()];
    for (int i = 0; i < m_obstacleVector.size(); ++i)
    {
        std::pair <std::string, std::map<std::string, int> > a = m_obstacleVector[i];
        m_obstacles[i].setHeight(a.second["height"]);
        m_obstacles[i].setSpacing(a.second["spacing"]);
        m_obstacles[i].setStartY(a.second["start-y"]);
        m_obstacles[i].setWidth(a.second["width"]);
    }
}

ObstacleFactory::~ObstacleFactory()
{
    delete[] m_obstacles;
}
