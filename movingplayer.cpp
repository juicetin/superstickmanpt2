//BUGS - CAN STILL JUMP INTO AN OBSTACLE

#include "movingplayer.h"

#include <iostream>
#include <cstdio>
using namespace std;

int counter = 0;

MovingPlayer::MovingPlayer(gameInfo game_info) :
    Player(game_info.image_path, game_info.size, game_info.x_initial),
    m_gravity(game_info.gravity), m_screen_width(game_info.x_dimension),
    m_screen_height(game_info.y_dimension),
    m_initial_jump_velocity(game_info.initial_jump_velocity)
{
    m_jumping = false;
    m_velocity_y = 0;
    m_collision = false;
    m_ground = 487-getSize() + 9*getSize()/1000 + getSize();
    m_relative_ground = 487-getSize() + 9*getSize()/1000 + getSize();
    m_next_relative_ground = m_ground;
    m_prev_obstacle_x_end = m_screen_width;
    m_prev_obst_index = -1;
    m_cur_obst_index = 0;
}

MovingPlayer::~MovingPlayer()
{

}

//ADDED - ALL BELOW

void MovingPlayer::collision_detection()
{
    bool x_collision = false, y_collision = false;
    int obst_left = (*m_obstacles)[m_cur_obst_index]->getX();
    int obst_width = static_cast<ObstacleRectangle*>((*m_obstacles)[m_cur_obst_index])->getWidth();
    int obst_top = (*m_obstacles)[m_cur_obst_index]->getY();
    int obst_height = static_cast<ObstacleRectangle*>((*m_obstacles)[m_cur_obst_index])->getHeight();
    int obst_right = obst_left + obst_width;
    int obst_bot = obst_top + obst_height;
    int obst_spacing = (*m_obstacles)[m_cur_obst_index]->getSpacing();

    //Sufficient conditions for two rectangular objects to touch/overlap
    m_collision = (get_player_left() <= obst_right)    //player left edge to left of obstacle right edge
            && (get_player_right() >= obst_left)     //player right edge to right of obstacle left edge
            && (get_player_top() < obst_bot)       //player top edge above obstacle bottom edge
            && (get_player_bottom() > obst_top);   //player bottom edge below obstacle top edge

    //Set next "relative ground level" once user ('s left) passes prev obstacle
    if (m_prev_obst_index != -1 && get_player_right() > (*m_obstacles)[m_prev_obst_index]->getX()
            + static_cast<ObstacleRectangle*>((*m_obstacles)[m_prev_obst_index])->getWidth())
    {
        //Set "relative ground level" back to real ground as necessary
        if ((*m_obstacles)[m_prev_obst_index]->getSpacing() > 150)
        {
            m_next_relative_ground = m_ground;
        }

        else if (obst_top > m_ground)
        {
            m_next_relative_ground = m_ground;
        }
        else
        {
            m_next_relative_ground = obst_top;
        }
    }
    else if (m_cur_obst_index == 0 && get_player_right() >= (*m_obstacles)[m_cur_obst_index]->getX())
    {
        m_next_relative_ground = obst_top;
    }

    //Set current GL to next GL once user jumps above it
    if (m_velocity_y >= 0 && get_player_bottom() < m_next_relative_ground)
    {
        m_relative_ground = m_next_relative_ground;
        m_collision = false;
    }

    //Change obstacle index to next once player passes current one
    if (get_player_right() > obst_right)
    {
        if (m_cur_obst_index + 1 < (*m_obstacles).size())
        {
            m_prev_obst_index = m_cur_obst_index;
            m_cur_obst_index++;
        }
        else
        {
            m_cur_obst_index = 0;
            m_prev_obst_index = ((*m_obstacles).size()) - 1;
        }
    }
}

void MovingPlayer::drop_player()
{
    if (get_player_bottom() - (m_velocity_y - m_gravity) < m_relative_ground)
    {
        m_velocity_y -= m_gravity;
    }
    else if (get_player_bottom() + 1 < m_relative_ground)
    {
        m_velocity_y = -1;
    }
    else
    {
        m_velocity_y = 0;
    }
}

void MovingPlayer::relative_ground_level_detection()
{
    bool x_collision = false, y_collision = false;
    int obst_left = (*m_obstacles)[m_cur_obst_index]->getX();
    int obst_width = static_cast<ObstacleRectangle*>((*m_obstacles)[m_cur_obst_index])->getWidth();
    int obst_top = (*m_obstacles)[m_cur_obst_index]->getY();
    int obst_height = static_cast<ObstacleRectangle*>((*m_obstacles)[m_cur_obst_index])->getHeight();
    int obst_right = obst_left + obst_width;
    int obst_bot = obst_top + obst_height;
    int obst_spacing = (*m_obstacles)[m_cur_obst_index]->getSpacing();

    //Dropping to new relative ground (from stationary y-velocity) level only occurs when not jumping
    if (!m_jumping && m_prev_obst_index != -1)
    {
        if (m_label->x() > (*m_obstacles)[m_prev_obst_index]->getX() +
                static_cast<ObstacleRectangle*>((*m_obstacles)[m_prev_obst_index])->getWidth()
                && get_player_bottom() < (*m_obstacles)[m_cur_obst_index]->getY())
        {
            drop_player();
        }
        else if (get_player_left() > (*m_obstacles)[m_prev_obst_index]->getX() +
                 static_cast<ObstacleRectangle*>((*m_obstacles)[m_prev_obst_index])->getWidth()
                 && get_player_bottom() < m_relative_ground)
        {
            drop_player();
        }
    }
}

//Move player up or down as part of jumping
void MovingPlayer::jump(bool update_flag, QPainter &painter)
{
    if (update_flag)
    {
        collision_detection();

        if (m_jumping)
        {
            m_velocity_y -= m_gravity;

            //Adjust player to ground level if velocity is too high
            if (m_velocity_y <= 0 && get_player_bottom() - m_velocity_y > m_relative_ground)
            {
                m_velocity_y = get_player_bottom() - m_relative_ground;
                m_jumping = false;
            }
        }
        else
        {
            m_velocity_y = 0;
            m_jumping = false;
        }

        relative_ground_level_detection();

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

int MovingPlayer::get_player_bottom()
{
    return m_label->y() + getSize();
}

int MovingPlayer::get_player_right()
{
    return m_label->x() + 150;
}

int MovingPlayer::get_player_left()
{
    return m_label->x();
}

int MovingPlayer::get_player_top()
{
    return m_label->y();
}

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
