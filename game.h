#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "background.h"

class Game
{
public:
    Game(Player * player, Background * background, int xDimension, int yDimension);
    ~Game();

    Player * getPlayer();
    Background * getBackground();

    const int& getXDimension() const;
    void setXDimension(const int& xDimension);

    const int& getYDimension() const;
    void setYDimension(const int& yDimension);

protected:
    Player * m_player;
    Background * m_background;
    int m_xDimension;
    int m_yDimension;


};

#endif // GAME_H
