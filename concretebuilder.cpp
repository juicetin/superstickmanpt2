#include "concretebuilder.h"

#include <cstdio>

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
}

ConcreteBuilder::~ConcreteBuilder()
{
    delete gb_fileReader;
}

//Fetches values from FileIO object and constructs Player object
MovingPlayer * ConcreteBuilder::buildPlayer()
{
    gameInfo game_info;

    game_info.image_path = gb_fileReader->getValues("player-image");
    game_info.size = gb_fileReader->getValues("player-size");
    game_info.x_initial = atoi(gb_fileReader->getValues("x-initial"));
    game_info.initial_jump_velocity = atoi(gb_fileReader->getValues("initial-jump-velocity"));
    game_info.gravity = atoi(gb_fileReader->getValues("gravity"));
    game_info.y_dimension = atoi(gb_fileReader->getValues("y-dimension"));

    return new MovingPlayer(game_info);
}

// //Fetches values from FileIO object and constructs Background object
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

//ObstacleCollection * ConcreteBuilder::buildObstacles()
//{
//    gameInfo game_info;
//    game_info.obstacle_speed = atoi(gb_fileReader->getValues("obstacle-speed"));
//    game_info.x_dimension = atoi(gb_fileReader->getValues("x-dimension"));
//    game_info.y_dimension = atoi(gb_fileReader->getValues("y-dimension"));
//    std::cout << "lelfail" << std::endl;
//    if (!gb_fileReader->getObstacleProperties().empty())
//        return new ObstacleCollection(gb_fileReader->getObstacleProperties(), game_info);
//}

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


