#ifndef OBSTACLEFACTORY_H
#define OBSTACLEFACTORY_H

#include <map>
#include <QMessageBox>
#include <string>

#include "gameinfo.h"
#include "obstaclerectangle.h"
#include "obstacleinfo.h"

class ObstacleFactory
{
public:
    static Obstacle *create(std::map<std::string, std::string> obstacle_info_map, gameInfo *game_info);
};

#endif // OBSTACLEFACTORY_H
