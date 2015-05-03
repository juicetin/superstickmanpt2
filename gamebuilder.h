#ifndef GAMEBUILDER
#define GAMEBUILDER

#include "background.h"
#include "game.h"
#include "player.h"
#include "movingplayer.h"
#include "fileio.h"
#include "movingplayerproxy.h"

//Handles FileIO and Game objects
class GameBuilder
{
public:

    GameBuilder() {}
    virtual ~GameBuilder() {}

//    virtual MovingPlayer * buildPlayer() = 0;
    virtual MovingPlayerProxy * buildPlayer() = 0;
    virtual Background * buildBackground() = 0;
    virtual Game * buildGame() = 0;

    // virtual ObstacleCollection * buildObstacles() = 0;

    virtual Game * getGame() = 0;
    virtual FileIO * getFileIO() = 0;

    virtual bool wasSuccessful() = 0;

protected:
    FileIO * gb_fileReader;
    bool m_wasSuccessful;

};



#endif // GAMEBUILDER

