#include "stdafx.h"

enum PLAYER_ANIMATION_STATES {IDLE, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Movement {
public:
    Movement();
    ~Movement();

    //Functions
    void playerMovement(sf::Sprite& playerSprite, int& moving);

protected:
};

