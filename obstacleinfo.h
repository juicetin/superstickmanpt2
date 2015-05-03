#ifndef OBSTACLEINFO
#define OBSTACLEINFO

#include <string>

struct obstacle_info {
	int x;
    int start_y;
    int width;
    int height;
    int spacing;
    int speed;
    std::string color;
}; typedef struct obstacle_info obstacleInfo;

#endif // OBSTACLEINFO

