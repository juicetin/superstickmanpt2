#include "movingplayer.h"

#include <iostream>

MovingPlayer::MovingPlayer(std::string imagePath, std::string size, int initialPosition, int jump_height) :
    Player(imagePath, size, initialPosition), m_jump_height(jump_height)
{
    m_jumping = false;
    m_velocity_y = 0;
    m_gravity = 3;
}

MovingPlayer::~MovingPlayer()
{

}

//ADDED - ALL BELOW

//Flag to indicate if player is in jumping trajectory
void MovingPlayer::set_jumping(bool asc_desc)
{
    m_jumping = asc_desc;
    m_velocity_y = 30;
}

bool MovingPlayer::is_jumping()
{
    return m_jumping;
}

//Move player up or down as part of jumping
void MovingPlayer::jump(bool *update_flag, int time, QPainter &painter)
{
    if (*update_flag)
    {
        *update_flag = false;
        int playerSize = getSize();

        //TODO Hard coded - will need to change for obstacle detection
        int current_ground = 487-playerSize + 9*playerSize/1000;

        if (m_jumping && m_label->y() <= current_ground)
        {
            //Execute jump imitating effects of gravity -
            //but force to ground/obstacle level if going
            //through them is imminent
            if (m_label->y() - m_velocity_y < current_ground)
            {
                m_label->move(m_label->x(), m_label->y() - m_velocity_y);
            }
            else
            {
                m_label->move(m_label->x(), current_ground);
                m_jumping = false;
            }
            m_velocity_y -= m_gravity;
        }
        //Reset jump related flags when jump is finished
        else if (m_jumping)
        {
            std::cout << "finished jumping\n";
            m_jumping = false;
        }
    }
}
