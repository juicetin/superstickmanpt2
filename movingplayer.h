#ifndef MOVINGPLAYER_H
#define MOVINGPLAYER_H

#include <string>
#include <cmath>

#include "player.h"

class MovingPlayer : public Player
{
public:
    MovingPlayer(std::string imagePath, std::string size, int initialPosition, int initial_jump_velocity, int gravity);
    ~MovingPlayer();

    void set_jumping(bool asc_desc);
    bool is_jumping();
    void jump(bool update_flag, QPainter &painter);

protected:
    int m_velocity_y;
    int m_gravity;
    int m_initial_jump_velocity;
    bool m_jumping;
};

#endif // MOVINGPLAYER_H
