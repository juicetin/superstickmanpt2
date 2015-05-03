#ifndef MOVINGPLAYERPROXY_H
#define MOVINGPLAYERPROXY_H

#include "renderableobject.h"
#include "movingplayer.h"
#include "gameinfo.h"

class MovingPlayerProxy : RenderableObject
{
public:
    MovingPlayerProxy(gameInfo game_info);
    void draw(QPainter &painter, bool collision);

    MovingPlayer m_moving_player;
};

#endif // MOVINGPLAYERPROXY_H
