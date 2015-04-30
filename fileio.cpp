#include "fileio.h"

//RAII - Opens file and processes data in one method on contruction
FileIO::FileIO(const char* fileLocation)
    : m_fileLocation(fileLocation)
{
    std::string line;
    int numLines = numberOfLines(m_fileLocation);

    std::ifstream inputStream(m_fileLocation);

    if (inputStream.is_open() || numLines != -1)
    {
        std::string* lines = new std::string [numLines];
        int index = 0;

        while (getline(inputStream, line))
        {
            lines[index++] = line;
        }
        inputStream.close();
        if (processLines(lines, numLines) >= 0) {
            m_wasSuccessful = true;
        } else {
            m_wasSuccessful = false;
        }

        delete[] lines ;
    } else {
        std::cout << "Could not open file!" << std::endl;
        m_wasSuccessful = false;
    }

}

FileIO::~FileIO()
{

}

//Skims through file to determine size of string array
int FileIO::numberOfLines(const char *fileLocation)
{
    int numLines = 0;
    std::string line;
    std::ifstream configFile;

    try {
        configFile.open(fileLocation);
    } catch (std::ifstream::failure e) {
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }

    if (configFile.is_open())
    {
        while (getline(configFile, line))
        {
            if (line[0] == '[') {

            }
            numLines++;
        }
        configFile.close();
    } else {
        numLines = -1;
    }

    return numLines;
}

//Stores data as key-value pairs in map configValues
int FileIO::processLines(std::string *lines, int numLines)
{
    int index = 0;
    std::string section;
    int numberOfConfigurations = 0;

    while (index < numLines)
    {
        if (lines[index][0] == '[') {
            section = lines[index];
            index++;
            continue;
        } else {
            std::string key;
            std::string value;
            key = lines[index].substr(0, lines[index].find('='));
            value = lines[index].substr(lines[index].find('=') + 1, lines[index].length());

            if (key.length() > 0 && value.length() > 0) {

                configValues[key] = value;
                numberOfConfigurations++;

            } else if (key.length() > 0 && value.length() <= 0) {
                std::cerr << "Invalid Config Data" << std::endl;
                return -1;
            } else {

            }
        }

        index++;


    }

    return 0;
}

//Returns the value matching the given key
const char* FileIO::getValues(std::string key)
{
    return configValues[key].c_str();
}

//Returns true if file was opened successfully and contained valid data
bool FileIO::wasSuccessful()
{
    return m_wasSuccessful;
}

//Saves the player's current position to the config file
void FileIO::saveGame(Game * game)
{
    std::ostringstream ss;
    ss << game->getPlayer()->getCurrentPosition();
    configValues["x-initial"] = ss.str();

    std::ofstream outStream;
    outStream.open(m_fileLocation);

    outStream << "[World]" << std::endl;
    outStream << "x-dimension=" << configValues["x-dimension"] << std::endl;
    outStream << "y-dimension=" << configValues["y-dimension"] << std::endl;
    outStream << "background-image=" << configValues["background-image"] << std::endl;
    outStream << "background-speed=" << configValues["background-speed"] << std::endl << std::endl;

    outStream << "[Player]" << std::endl;
    outStream << "player-image=" << configValues["player-image"] << std::endl;
    outStream << "player-size=" << configValues["player-size"] << std::endl;
    outStream << "x-initial=" << configValues["x-initial"] << std::endl;

}
