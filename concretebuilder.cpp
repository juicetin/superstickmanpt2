#include "concretebuilder.h"

//Initialise FileIO for config file and build game
ConcreteBuilder::ConcreteBuilder()
{
    gb_fileReader = new FileIO("../superstickmanpt2/config.ini");

    if (gb_fileReader->wasSuccessful()) {
        m_wasSuccessful = true;
        m_game = buildGame();
    } else {
        m_wasSuccessful = false;
    }

    ObstacleFactory test(gb_fileReader->getObstacleProperties());

}

ConcreteBuilder::~ConcreteBuilder()
{
    delete gb_fileReader;
}

//Fetches values from FileIO object and constructs Player object
MovingPlayer * ConcreteBuilder::buildPlayer()
{
    std::string imagePath = gb_fileReader->getValues("player-image");
    std::string playerSize = gb_fileReader->getValues("player-size");
    int initialPosition = atoi(gb_fileReader->getValues("x-initial"));

    //Added - jump height
    std::string jump_height_key = playerSize;
    jump_height_key.append("-jumpheight");
    int jumpHeight = atoi(gb_fileReader->getValues(jump_height_key));
    return new MovingPlayer(imagePath, playerSize, initialPosition, jumpHeight);
}

//Fetches values from FileIO object and constructs Background object
Background * ConcreteBuilder::buildBackground()
{
    std::string imagePath = gb_fileReader->getValues("background-image");
    int scrollSpeed = atoi(gb_fileReader->getValues("background-speed"));

    return new Background(imagePath, scrollSpeed);
}

//Fetches values from FileIO object and constructs Game object from game components
Game * ConcreteBuilder::buildGame()
{
    int xDimension = atoi(gb_fileReader->getValues("x-dimension"));
    int yDimension = atoi(gb_fileReader->getValues("y-dimension"));

    return new Game(buildPlayer(), buildBackground(), xDimension, yDimension);
}

//Returns a pointer to the Game object
Game * ConcreteBuilder::getGame()
{
    return m_game;
}

FileIO * ConcreteBuilder::getFileIO()
{
    return gb_fileReader;
}

//Returns true if the game built successfully
bool ConcreteBuilder::wasSuccessful()
{
    return m_wasSuccessful;
}


