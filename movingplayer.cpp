#include "movingplayer.h"

MovingPlayer::MovingPlayer(std::string imagePath, std::string size, int initialPosition, int jump_height) :
    Player(imagePath, size, initialPosition), m_jump_height(jump_height)
{
    m_jump_ascend = true;
    m_jumping = false;
}

MovingPlayer::~MovingPlayer()
{

}

//ADDED - ALL BELOW

//Flag to indicate if player is in jumping trajectory
void MovingPlayer::set_jumping(bool asc_desc)
{
    m_jumping = asc_desc;
}

//Move player up or down as part of jumping
void MovingPlayer::jump(bool *update_flag, int time, QPainter &painter)
{
    if (*update_flag)
    {
        *update_flag = false;
        int playerSize = getSize();
        int current_ground = 487-playerSize + 9*playerSize/1000;

        //Ascent of jump
        //TODO - change hard coded jump cap
        if (m_jumping && m_label->y() > 250 && m_jump_ascend)
        {
            m_label->move(m_label->x(), m_label->y() - 25);
        }
        //Descent of jump
        else if (m_jumping && m_label->y() < current_ground)
        {
            m_jump_ascend = false;
            m_label->move(m_label->x(), m_label->y() + 25);
        }
        //Reset jump related flags when jump is finished
        else if (m_jumping)
        {
            m_label->move(m_label->x(), current_ground);
            m_jump_ascend = true;
            m_jumping = false;
        }
    }
}
