#include "stdafx.h"
#include "Player.h"

Player::Player() {
    this->initSprite();
    this->initTexture();
}

Player::~Player() {

}

void Player::initSprite() {

}

void Player::initTexture() {

}

void Player::update() {
    
}
void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}
