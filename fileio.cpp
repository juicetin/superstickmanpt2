#include "fileio.h"

#include <cstdio>

//RAII - Opens file and processes data in one method on contruction
FileIO::FileIO(const char* fileLocation)
    : m_fileLocation(fileLocation)
{
    std::string line;
    int numLines = numberOfLines(m_fileLocation);

    valid_obstacle_properties["start-y"] = true;
    valid_obstacle_properties["height"] = true;
    valid_obstacle_properties["width"] = true;
    valid_obstacle_properties["spacing"] = true;

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
            numLines++;
        }
        configFile.close();
    } else {
        numLines = -1;
    }
    return numLines;
}

//ADDED - Stores an obstacle item
int FileIO::storeObstacleData(std::string value, std::string key)
{
    std::map<std::string, int> obstacle;
    std::vector<std::string> obstacle_properties;
    std::stringstream ss(value);
    std::string item;
    int property_count = 0;
    while (std::getline(ss, item, ','))
    {
        property_count++;
        std::string property_key = item.substr(0, item.find(":"));
        int property_value = atoi(item.substr(item.find(":") + 1, item.length()).c_str());
        obstacle[property_key] = property_value;
        if (property_key.length() <= 0 ||
                valid_obstacle_properties[property_key] != true)
        {
            std::cerr << "Invalid obstacle property" << std::endl;
            return -1;
        }
        else if (property_value <= 0)
        {
            std::cerr << "Invalid obstacle property value" << std::endl;
            return -1;
        }
    }
    if (property_count < 4)
    {
        return -1;
    }
    obstaclesProperties.push_back(std::make_pair(key, obstacle));
    return 0;
}

//Changed - Stores data as key-value pairs in map configValues
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

                //Modified for obstacles
                std::size_t found = key.find("obstacle");
                if (found == std::string::npos) {
                    configValues[key] = value;
                } else {
                    if (storeObstacleData(value, key) != 0)
                    {
                        std::cerr << "Terminated due to invalid obstacle config data: see above" << std::endl;
                        return -1;
                    }
                }
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
