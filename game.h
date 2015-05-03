#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "movingplayer.h"
#include "background.h"
#include "obstaclecollection.h"
#include "movingplayerproxy.h"

class Game
{
public:
    Game(MovingPlayerProxy * player, Background * background, int xDimension, int yDimension);
    ~Game();

//    MovingPlayer * getPlayer();
    MovingPlayerProxy * getPlayer();
    Background * getBackground();

    const int& getXDimension() const;
    void setXDimension(const int& xDimension);

    const int& getYDimension() const;
    void setYDimension(const int& yDimension);

    void setObstacles(ObstacleCollection * obstacles);
    ObstacleCollection * getObstacles();

protected:
//    MovingPlayer * m_player;
    MovingPlayerProxy * m_player;
    Background * m_background;
    ObstacleCollection * m_obstacles;

    int m_xDimension;
    int m_yDimension;


};

#endif // GAME_H
