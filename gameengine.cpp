#include "gameengine.h"

//Construct new ConcreteBuilder and Dialog objects
GameEngine::GameEngine()
{
    g_builder = new ConcreteBuilder();
    g_window = new Dialog();

    //If gamebuilder is successful, start the game
    if (g_builder->wasSuccessful()) {
        g_running = true;
        start();
    } else {
        g_running = false;
    }
}

//Delete dynamically allocated objects
GameEngine::~GameEngine()
{
    delete g_builder;
    delete g_window;
}

//Builds game and sets Dialog up for animation
void GameEngine::start()
{
    g_builder->buildGame();
    g_window->setGame(g_builder->getGame());
    g_window->setFileIO(g_builder->getFileIO());
    g_window->show();
}

//Returns true if the game built successfully
bool GameEngine::running()
{
    return g_running;
}

