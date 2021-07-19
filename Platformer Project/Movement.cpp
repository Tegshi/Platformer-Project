#include "stdafx.h"
#include "Movement.h"

Movement::Movement() {
}

Movement::~Movement() {
}

//arrow keys to control sprite.
//doesn't use this->playerSprite because its referring 
//to a sprite that isn't in this movement class
void Movement::playerMovement(sf::Sprite& playerSprite, int& animState) {
    animState = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        playerSprite.move(-5.f, 0.f);
        animState = MOVING_LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        playerSprite.move(5.f, 0.f);
        animState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        playerSprite.move(0.f, -5.f);
        animState = JUMPING;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        playerSprite.move(0.f, 5.f);
        animState = FALLING;
    }
}
