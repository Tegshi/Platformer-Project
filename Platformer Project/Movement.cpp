#include "stdafx.h"
#include "Movement.h"

Movement::Movement() {
}

Movement::~Movement() {
}

void Movement::playerMovement(sf::Sprite& playerSprite) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        playerSprite.move(-1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        playerSprite.move(1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        playerSprite.move(0.f, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        playerSprite.move(0.f, 1.f);
}
