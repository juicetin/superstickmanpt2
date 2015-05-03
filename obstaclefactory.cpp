#include "obstaclefactory.h"

Obstacle *ObstacleFactory::create(std::map<std::string, std::string> obstacle_info_map, gameInfo *game_info)
{

    int type = atoi(obstacle_info_map["type"].c_str());

	//Properties required by all obstacles
	obstacleInfo obstacle_info;
    obstacle_info.start_y = atoi(obstacle_info_map["start-y"].c_str());
    obstacle_info.spacing = atoi(obstacle_info_map["spacing"].c_str());
    obstacle_info.speed = game_info->obstacle_speed;
    obstacle_info.color = obstacle_info_map["color"];

	//Rectangles
	if (type == 0)
	{
        obstacle_info.height = atoi(obstacle_info_map["height"].c_str());
        obstacle_info.width = atoi(obstacle_info_map["width"].c_str());
        return new ObstacleRectangle(obstacle_info, game_info);
	}
	else
	{
		QMessageBox error;
		error.setText("Incorrect obstacle type detected\n" );
		error.exec();
		return NULL;
	}
}
