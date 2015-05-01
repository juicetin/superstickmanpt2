#ifndef OBSTACLEFACTORY_H
#define OBSTACLEFACTORY_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "obstacle.h"

typedef std::vector <std::pair<std::string, std::map<std::string, int> > > obstaclevector;

class ObstacleFactory
{
public:
    ObstacleFactory(std::vector <std::pair<std::string, std::map<std::string, int> > > obstacleVector);
    ~ObstacleFactory();

protected:
    Obstacle *m_obstacles;
    std::vector <std::pair<std::string, std::map<std::string, int> > > m_obstacleVector;
};

#endif // OBSTACLEFACTORY_H
