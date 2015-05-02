#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "movingplayer.h"
#include "background.h"
#include "obstaclecollection.h"

class Game
{
public:
    Game(ObstacleCollection * obstacles, MovingPlayer * player, Background * background, int xDimension, int yDimension);
    ~Game();

    MovingPlayer * getPlayer();
    Background * getBackground();

    const int& getXDimension() const;
    void setXDimension(const int& xDimension);

    const int& getYDimension() const;
    void setYDimension(const int& yDimension);

    ObstacleCollection * getObstacles();

protected:
    MovingPlayer * m_player;
    Background * m_background;
    ObstacleCollection * m_obstacles;

    int m_xDimension;
    int m_yDimension;


};

#endif // GAME_H
