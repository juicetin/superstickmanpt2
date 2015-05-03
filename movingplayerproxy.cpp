#include "movingplayerproxy.h"

MovingPlayerProxy::MovingPlayerProxy(gameInfo game_info) : m_moving_player(game_info)
{

}

void MovingPlayerProxy::draw(QPainter &painter, bool update)
{

    if (m_moving_player.in_screen())
    {
        m_moving_player.jump(update, painter);
    }
}
