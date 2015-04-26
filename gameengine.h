#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <cstdlib>

#include "dialog.h"
#include "concretebuilder.h"

//Issues build commands to the GameBuilder, and creates and keeps track of the Dialog object
class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void buildGame();
    void start();

    bool running();

protected:
    GameBuilder * g_builder;
    Dialog * g_window;

    bool g_running;
};

#endif // GAMEENGINE_H
