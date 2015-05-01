#ifndef OBSTACLECOLLECTION_H
#define OBSTACLECOLLECTION_H

#include <QPainter>
#include <vector>
#include <map>

#include "obstacle.h"
#include "obstaclerectangle.h"

class ObstacleCollection
{
public:
    ObstacleCollection(std::vector<std::map<std::string, int > > obstacles_vector, int obstacle_speed, int width);
    ~ObstacleCollection();
    void renderObstacles(bool update_flag, QPainter &painter, bool animated);

private:
    std::vector<Obstacle*> m_obstacles;
    int m_speed;
    int m_obstacle_loop_length;
    int m_width;
};

#endif // OBSTACLECOLLECTION_H
