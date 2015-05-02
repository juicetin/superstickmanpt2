#include "obstaclefactory.h"

Obstacle *ObstacleFactory::create(std::map<std::string, int> obstacle_info_map, gameInfo *game_info)
{

	int type = obstacle_info_map["type"];

	//Properties required by all obstacles
	obstacleInfo obstacle_info;
    obstacle_info.start_y = obstacle_info_map["start-y"];
    obstacle_info.spacing = obstacle_info_map["spacing"];
    obstacle_info.speed = game_info->obstacle_speed;

	//Rectangles
	if (type == 0)
	{
        obstacle_info.height = obstacle_info_map["height"];
        obstacle_info.width = obstacle_info_map["width"];
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
