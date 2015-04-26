#ifndef GAMEBUILDER
#define GAMEBUILDER

#include "background.h"
#include "game.h"
#include "player.h"
#include "fileio.h"

//Handles fileIO and Game objects
class GameBuilder
{
public:

    GameBuilder() {}
    virtual ~GameBuilder() {}

    virtual Player * buildPlayer() = 0;
    virtual Background * buildBackground() = 0;
    virtual Game * buildGame() = 0;

    virtual Game * getGame() = 0;
    virtual fileIO * getFileIO() = 0;

    virtual bool wasSuccessful() = 0;

protected:
    fileIO * gb_fileReader;
    bool m_wasSuccessful;

};



#endif // GAMEBUILDER

