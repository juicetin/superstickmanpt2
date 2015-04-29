#ifndef MOVINGPLAYER_H
#define MOVINGPLAYER_H

#include <string>

#include "player.h"

class MovingPlayer : public Player
{
public:
    MovingPlayer(std::string imagePath, std::string size, int initialPosition);

protected:

};

#endif // MOVINGPLAYER_H
