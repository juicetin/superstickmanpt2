#include "fileio.h"

#include <cstdio>

//RAII - Opens file and processes data in one method on contruction
FileIO::FileIO(const char* fileLocation)
    : m_fileLocation(fileLocation)
{
    std::string line;
    int numLines = numberOfLines(m_fileLocation);

    m_valid_obstacle_properties["start-y"] = true;
    m_valid_obstacle_properties["height"] = true;
    m_valid_obstacle_properties["width"] = true;
    m_valid_obstacle_properties["spacing"] = true;
    m_valid_obstacle_properties["type"] = true;

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
int FileIO::storeObstacleData(std::string data)
{
    if (data.length() == 0)
    {
        return 0;
    }

    std::map<std::string, int> obstacle;
    std::stringstream ss(data);
    std::string item;
    int property_count = 0;
    while (std::getline(ss, item, ','))
    {
        property_count++;
        std::string property_key = item.substr(0, item.find(":"));
        int property_value = atoi(item.substr(item.find(":") + 1, item.length()).c_str());
       obstacle[property_key] = property_value;
        if (property_key.length() <= 0 ||
                m_valid_obstacle_properties[property_key] != true)
        {
            QMessageBox msgBox;
            std::string error = "Invalid obstacle property: ";
            error.append(property_key);
            msgBox.setText(error.c_str());
            msgBox.exec();
            std::cerr << "Invalid obstacle property " << property_key << std::endl;
            return -1;
        }
        else if (property_value < 0)
        {
            QMessageBox msgBox;
            std::string error = "Invalid obstacle value: [";
            error.append(item.substr(item.find(":") + 1, item.length()).c_str())
                    .append("] for obstacle property: ")
                    .append(property_key);
            msgBox.setText(error.c_str());
            msgBox.exec();
            std::cerr << "Invalid obstacle property value" << std::endl;
            return -1;
        }
    }
    if (property_count < 5)
    {
        return -1;
    }
    m_obstaclesProperties.push_back(obstacle);
    return 0;
}

std::vector<std::map<std::string, int> > FileIO::getObstacleProperties()
{
    return m_obstaclesProperties;
}

//Changed - Stores data as key-value pairs in map configValues
int FileIO::processLines(std::string *lines, int numLines)
{
    int index = 0;
    std::string section;
    int numberOfConfigurations = 0;

    while (index < numLines)
    {
        if (lines[index][0] == '-' && lines[index][1] == '-')
        {
            index++;
            continue;
        }
        else if (lines[index][0] == '[') {
            section = lines[index];
            index++;
            continue;
        }
        else
        {
            if (section.compare("[Obstacle-list]") != 0)
            {
                std::string key;
                std::string value;
                key = lines[index].substr(0, lines[index].find('='));
                value = lines[index].substr(lines[index].find('=') + 1, lines[index].length());

                if (key.length() > 0 && value.length() > 0) {
                    configValues[key] = value;
                    numberOfConfigurations++;
                }
                else if (key.length() > 0 && value.length() <= 0)
                {
                    std::cerr << "Invalid Config Data" << std::endl;
                    return -1;
                }
            }
            //Obstacles parsing block
            else
            {
                if (storeObstacleData(lines[index]) != 0)
                {
                    return -1;
                }
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

    outStream << "initial-jump-velocity=" << configValues["initial-jump-velocity"] << std::endl;
    outStream << "gravity=" << configValues["gravity"] << std::endl << std::endl;

    outStream << "[Obstacles]" << std::endl;
    outStream << "obstacle-speed=" << configValues["obstacle-speed"] << std::endl << std::endl; 

    outStream << "[Obstacle-list]" << std::endl;

    outStream << "--Order of the properties can be given in any order, so long as all are present." << std::endl <<
                "--All shapes require a type, start-y, and spacing, as a minimum." << std::endl <<
                "--(Note that the spacing on the last obstacle is ignored.)" << std::endl <<
                "--The following types of shapes are available:" << std::endl <<
                "--0(rectangle)" << std::endl <<
                "--Shapes have the following additional requirements:" << std::endl <<
                "--Rectangle - height, width" << std::endl;

    for (int i = 0; i < m_obstaclesProperties.size(); ++i)
    {
        int type = m_obstaclesProperties[i]["type"];
        int start_y = m_obstaclesProperties[i]["start-y"];
        int height = m_obstaclesProperties[i]["height"];
        int width = m_obstaclesProperties[i]["width"];
        int spacing = m_obstaclesProperties[i]["spacing"];
        outStream << "type:" << type << ",start-y:" << start_y << ",height:" << height << ",width:" << width << ",spacing:" << spacing << std::endl;
    }
}
