#ifndef GAMEINFO
#define GAMEINFO

#include <string>

struct game_info{
    int x_dimension;
    int y_dimension;
    int background_speed;
    int x_initial;
    int initial_jump_velocity;
    int gravity;
    int obstacle_speed;
    int obstacle_loop_length;
    std::string image_path;
    std::string size;
}; typedef struct game_info gameInfo;

#endif // GAMEINFO

