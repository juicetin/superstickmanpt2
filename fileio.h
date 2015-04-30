#ifndef FILEIO_H
#define FILEIO_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "game.h"

//Reads from and saves to the config file
//Stores key value pairs in map
class FileIO
{
public:
    FileIO(const char* fileLocation);
    ~FileIO();

    int numberOfLines(const char* fileLocation);

    //Added
    int storeObstacleData(std::string value, std::string key);

    int processLines(std::string* lines, int numLines);

    const char* getValues(std::string key);

    bool wasSuccessful();

    void saveGame(Game * game);

protected:
    const char* m_fileLocation;
    std::map <std::string, std::string> configValues;
    bool m_wasSuccessful;

    //Added
    std::vector <std::pair<std::string, std::map<std::string, int> > > obstaclesProperties;
    std::map <std::string, bool> valid_obstacle_properties;
};

#endif // FILEIO_H
