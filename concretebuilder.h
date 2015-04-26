#ifndef CONCRETEBUILDER_H
#define CONCRETEBUILDER_H

#include <cstdlib>

#include "gamebuilder.h"

//Inherits the abstract Gamebuilder class, and keeps track of the created Game object
class ConcreteBuilder : public GameBuilder
{
public:
    ConcreteBuilder();
    ~ConcreteBuilder();

    virtual Player * buildPlayer();

    virtual Background * buildBackground();

    virtual Game * buildGame();

    Game * getGame();
    fileIO * getFileIO();

    virtual bool wasSuccessful();

protected:
    Game * m_game;

};

#endif // CONCRETEBUILDER_H
