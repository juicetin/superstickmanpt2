#include "game.h"

Game::Game(MovingPlayer * player, Background * background, int xDimension, int yDimension)
    : m_player(player),
      m_background(background),
      m_xDimension(xDimension),
      m_yDimension(yDimension)
{

}

Game::~Game()
{
    //Player and Background objects handle their own deletion
}

//Returns the game's player object
MovingPlayer * Game::getPlayer()
{
    return m_player;
}

//Returns the game's background object
Background * Game::getBackground()
{
    return m_background;
}

//Returns the game window width
const int& Game::getXDimension() const
{
    return m_xDimension;
}

//Sets the window width to the given int
void Game::setXDimension(const int &xDimension)
{
    m_xDimension = xDimension;
}

//Returns the game window height
const int& Game::getYDimension() const
{
    return m_yDimension;
}

//Sets the window height to the given int
void Game::setYDimension(const int &yDimension)
{
    m_yDimension = yDimension;
}


