#ifndef OBSTACLECOLLECTION_H
#define OBSTACLECOLLECTION_H

#include <QPainter>
#include <vector>
#include <map>

#include "obstacle.h"
#include "obstaclerectangle.h"
#include "gameinfo.h"
#include "obstaclefactory.h"

class ObstacleCollection
{
public:
    ObstacleCollection(std::vector<std::map<std::string, int > > obstacles_vector, gameInfo game_info);
    ~ObstacleCollection();
    void renderObstacles(bool update_flag, QPainter &painter, bool animated);

    std::vector<Obstacle*> * getObstacles();

    void setCollision(bool * collision);

private:
    std::vector<Obstacle*> m_obstacles;
    int m_speed;
    int m_width;
    int m_height;
    gameInfo m_game_info;

    bool * m_collision;
};

#endif // OBSTACLECOLLECTION_H
