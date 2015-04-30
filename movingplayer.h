#ifndef MOVINGPLAYER_H
#define MOVINGPLAYER_H

#include <string>

#include "player.h"

class MovingPlayer : public Player
{
public:
    MovingPlayer(std::string imagePath, std::string size, int initialPosition, int jump_height);
    ~MovingPlayer();

    //ADDED
    void set_jumping(bool asc_desc);
    bool is_jumping();
    void jump(bool *update_flag, int time, QPainter &painter);

protected:
    //ADDED
    int m_velocity_y;
    int m_gravity;
    int m_jump_height;
    bool m_jumping;
};

#endif // MOVINGPLAYER_H
