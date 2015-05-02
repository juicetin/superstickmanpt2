#ifndef MOVINGPLAYER_H
#define MOVINGPLAYER_H

#include <string>
#include <cmath>

#include "player.h"
#include "gameinfo.h"
#include "obstaclerectangle.h"
#include "obstacleinfo.h"

class MovingPlayer : public Player
{
public:
    MovingPlayer(gameInfo game_info);
    ~MovingPlayer();

    void set_jumping(bool asc_desc);
    bool is_jumping();
    void jump(bool update_flag, QPainter &painter);

    void set_obstacle_list_pointer(std::vector<Obstacle*> * obstacles);

    bool * get_collision();

protected:
    int m_velocity_y;
    int m_gravity;
    int m_screen_height;
    int m_screen_width;
    int m_ground;
    int m_relative_ground;
    int m_initial_jump_velocity;
    bool m_jumping;
    bool m_collision;
    gameInfo current_obstacle;
    std::vector<Obstacle*> * m_obstacles;
};

#endif // MOVINGPLAYER_H
