#ifndef FILEIOADAPTER_H
#define FILEIOADAPTER_H

#include "obstaclesfileio.h"
#include "fileio.h"

#include <string>

class FileIOAdapter : public ObstaclesFileIO, protected FileIO
{
public:
    FileIOAdapter();
    void processAllLines (std::string *lines, int numLines);
};

#endif // FILEIOADAPTER_H
