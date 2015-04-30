#ifndef FILEIO_H
#define FILEIO_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

#include "game.h"

//Reads from and saves to the config file
//Stores key value pairs in map
class FileIO
{
public:
    FileIO(const char* fileLocation);
    ~FileIO();

    int numberOfLines(const char* fileLocation);

    int processLines(std::string* lines, int numLines);

    const char* getValues(std::string key);

    bool wasSuccessful();

    void saveGame(Game * game);

protected:
    const char* m_fileLocation;


    std::map <std::string, std::string> configValues;



    bool m_wasSuccessful;
};

#endif // FILEIO_H
