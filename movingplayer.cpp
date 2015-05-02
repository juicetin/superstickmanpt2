#include "movingplayer.h"

#include <iostream>
#include <cstdio>

MovingPlayer::MovingPlayer(gameInfo game_info) :
Player(game_info.image_path, game_info.size, game_info.x_initial),
m_gravity(game_info.gravity), m_screen_width(game_info.x_dimension),
m_screen_height(game_info.y_dimension),
m_initial_jump_velocity(game_info.initial_jump_velocity)
{
    m_jumping = false;
    m_velocity_y = 0;
    m_collision = false;
    m_ground = 487-getSize() + 9*getSize()/1000;
    m_relative_ground = 487-getSize() + 9*getSize()/1000;
}

MovingPlayer::~MovingPlayer()
{

}

//ADDED - ALL BELOW

//Flag to indicate if player is in jumping trajectory
void MovingPlayer::set_jumping(bool asc_desc)
{
    m_jumping = asc_desc;
    m_velocity_y = m_initial_jump_velocity;
}

bool MovingPlayer::is_jumping()
{
    return m_jumping;
}

//Move player up or down as part of jumping
void MovingPlayer::jump(bool update_flag, QPainter &painter)
{
    if (update_flag)
    {
        m_collision = false;
        int playerSize = getSize();
        int obst_x = -1, obst_width = -1, obst_y = -1, obst_height = -1;
        bool x_overlap, y_overlap;
        for (int i = 0; i < (*m_obstacles).size(); ++i)
        {
            obst_x = (*m_obstacles)[i]->getX();
            obst_width = static_cast<ObstacleRectangle*>((*m_obstacles)[i])->getWidth();

            //When within screen bounds
            if (obst_x + obst_width > 0 && obst_x < m_screen_width)
            {
                obst_y = (*m_obstacles)[i]->getY();
                obst_height = static_cast<ObstacleRectangle*>((*m_obstacles)[i])->getHeight(); 

                x_overlap = false;
                //When top left corner of stickman is less than the end of the obstacle
                if (m_label->x() < obst_x + obst_width)
                {
                    x_overlap = obst_x + obst_width - (m_label->x()+130) < obst_width;
                }

                y_overlap = false;
                int player_bottom = m_label->y() + getSize();
                int obstacle_bottom = obst_y + obst_height;
                if (player_bottom <= obstacle_bottom)
                {
                    y_overlap = player_bottom >= obst_y;
                }
                else if (player_bottom > obstacle_bottom)
                {
                    y_overlap = player_bottom >= obst_y;
                }

                if (x_overlap && y_overlap)
                {
                    m_collision = true;
                    m_relative_ground = obst_y - (m_screen_height - (487-playerSize + 9*playerSize/1000 + playerSize - 10));
                    break;
                }
            }
        }

        //TODO Hard coded - will need to change for obstacle detection
        bool obstacle_flag = false;

        if (m_jumping)
        {
            if (m_label->y() - m_velocity_y <= m_relative_ground)
            {
                m_velocity_y -= m_gravity;
            }
            else if (m_velocity_y < 0 && m_velocity_y <= m_relative_ground)
            {
                m_jumping = false;
                m_label->move(m_label->x(), m_relative_ground);
                m_velocity_y = 0;
            }
            else
            {
                m_velocity_y -= m_gravity;
            }
        }
        else
        {
            m_jumping = false;
            m_velocity_y = 0;
        }

        m_label->move(m_label->x(), m_label->y() - m_velocity_y);
    }
}

void MovingPlayer::set_obstacle_list_pointer(std::vector<Obstacle*> * obstacles)
{
    m_obstacles = obstacles;
}

bool * MovingPlayer::get_collision()
{
    return &m_collision;
}
