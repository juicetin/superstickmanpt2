#ifndef CONCRETEBUILDER_H
#define CONCRETEBUILDER_H

#include <cstdlib>

#include "gamebuilder.h"
#include "gameinfo.h"
#include "movingplayerproxy.h"

//Inherits the abstract Gamebuilder class, and keeps track of the created Game object
class ConcreteBuilder : public GameBuilder
{
public:
    ConcreteBuilder();
    ~ConcreteBuilder();

//    virtual MovingPlayer * buildPlayer();
    virtual MovingPlayerProxy * buildPlayer();

    virtual Background * buildBackground();

    virtual Game * buildGame();

    // virtual ObstacleCollection * buildObstacles();

    Game * getGame();
    FileIO * getFileIO();

    virtual bool wasSuccessful();

protected:
    Game * m_game;

};

#endif // CONCRETEBUILDER_H
