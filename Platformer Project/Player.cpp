#include "stdafx.h"
#include "Player.h"

Player::Player() {
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimation();
}

Player::~Player() {
    delete this->movement;
}

void Player::initVariables() {
    this->animState = IDLE;
}

void Player::initTexture() {
    // 641 x 3388 kirby_sprite.png
    if (!this->textureSheet.loadFromFile("Textures/kirby_sprite_simple.png"))
        std::cout << "ERROR::PLAYER::Couldn't load player texture!" << std::endl;
}
void Player::initSprite() {
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(0, 0, 34, 35);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(10.5f, 10.5f);
}

void Player::initMovement() {
    this->movement = new Movement();
}

void Player::initAnimation() {
    this->animationTimer.restart();
}

void Player::update() {
    this->updatePlayer();
    this->updateAnimation();
}

void Player::updatePlayer() {
    this->movement->playerMovement(this->sprite, this->animState);
}
 
void Player::updateAnimation() {
    if (this->animState == IDLE) {  
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
            this->currentFrame.top = 0;
            this->currentFrame.left += 29;
            if (this->currentFrame.left >= 87)
                this->currentFrame.left = 0;
        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
        }
    }
    else if (this->animState == MOVING_RIGHT) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
            this->currentFrame.top = 89;
            this->currentFrame.left += 31;
            if (this->currentFrame.left >= 194)
                this->currentFrame.left = 0;
        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
        }
    }
    else {
        this->animationTimer.restart();
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}
