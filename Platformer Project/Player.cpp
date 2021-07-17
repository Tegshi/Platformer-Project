#include "stdafx.h"
#include "Player.h"

Player::Player() {
    this->initTexture();
    this->initSprite();
}

Player::~Player() {
    delete this->movement;
}

void Player::initSprite() {
    this->sprite.setTexture(this->textureSheet);
}

void Player::initTexture() {
    if (!this->textureSheet.loadFromFile("Textures/slime.png"))
        std::cout << "ERROR::PLAYER::Couldn't load player texture!" << std::endl;
}

void Player::initMovement() {
    this->movement = new Movement();
}

void Player::update() {
    this->updatePlayer();
}

void Player::updatePlayer() {
    this->movement->playerMovement(this->sprite);
}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}
