#include "stdafx.h"
#include "Player.h"

Player::Player() {
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimation();
    this->initPhysics();
}

Player::~Player() {
}

const bool& Player::getAnimSwitch() {
    bool anim_switch = this->animSwitch;

    if (this->animSwitch)
        this->animSwitch = false;
    return anim_switch;
}

const sf::FloatRect Player::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const {
    return this->sprite.getPosition();
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Player::resetVelocityY() {
    this->velocity.y = 0;
}

void Player::initVariables() {
    this->animState = IDLE;
}

void Player::initTexture() {
    if (!this->textureSheet.loadFromFile("Textures/kirby_downsize.png"))
        std::cout << "ERROR::PLAYER::Couldn't load player texture!" << std::endl;
}

void Player::initSprite() {
    this->sprite.setTexture(this->textureSheet);
    //this->currentFrame = sf::IntRect(0, 0, 34, 35);
    this->currentFrame = sf::IntRect(0, 0, 32, 30);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(10, 10);
}

void Player::initAnimation() {
    this->animationTimer.restart();
    this->animSwitch = true;
}

void Player::initPhysics() {
    this->maxVelocity = 10;
    this->minVelocity = 1;
    this->acceleration = 3;
    this->drag = 0.93;
    this->gravity = 5;
    this->maxGravity = 4;
}

void Player::update() {
    this->updatePlayer();
    this->updateAnimation();
    this->updatePhysics();
}

void Player::updatePlayer() {
    animState = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->move(-5, 0);
        animState = MOVING_LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->move(5, 0);
        animState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->move(0, -5);
        animState = JUMPING;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->move(0, 5);
        animState = FALLING;
    }
}
 
void Player::updateAnimation() {
    if (this->animState == IDLE) {  
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch()) {
            this->currentFrame.top = 0;
            this->currentFrame.left += 30;
            if (this->currentFrame.left >= 87)
                this->currentFrame.left = 0;
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }
    else if (this->animState == MOVING_RIGHT) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
            this->currentFrame.top = 90;
            this->currentFrame.left += 31;
            if (this->currentFrame.left >= 240)
                this->currentFrame.left = 0;
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
        
        this->sprite.setScale(10, 10);
        this->sprite.setOrigin(0, 0);
    }
    else if (this->animState == MOVING_LEFT) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
            this->currentFrame.top = 90;
            this->currentFrame.left += 31;
            if (this->currentFrame.left >= 240)
                this->currentFrame.left = 0;
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
           
        this->sprite.setScale(-10, 10);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width/10, 0);
    }
    else 
        this->animationTimer.restart();
}

void Player::resetAnimationTimer() {
    this->animationTimer.restart();
    this->animSwitch = true;
}

void Player::updatePhysics() {
    //Gravity
    this->velocity.y += 2 * this->gravity;

    if (std::abs(this->velocity.x) > this->maxGravity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        this->velocity.y = this->maxGravity * ((this->velocity.y < 0) ? -1 : 1);
    }


    //Drag, lowers velocity value by 0.98 over time
    this->velocity *= this->drag;

    //Limit drag, basically once you reach a certain
    //minimum velocity, you stop moving
    if (std::abs(this->velocity.x) < this->minVelocity)
        this->velocity.x = 0;
    if (std::abs(this->velocity.y) < this->minVelocity)
        this->velocity.y = 0;

    this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y) {
    //Acceleration
    this->velocity.x += dir_x * this->acceleration;
    //this->velocity.y += dir_y * this->acceleration; //not really used, we use gravity
    this->velocity.y = dir_y * this->acceleration;

    //Limit velocity/acceleration
    if (std::abs(this->velocity.x) > this->maxVelocity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0) ? -1 : 1);
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);

    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(4);
    circle.setPosition(this->sprite.getPosition());
    target.draw(circle);
}
