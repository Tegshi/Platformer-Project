#include "stdafx.h"
#include "Player.h"

Player::Player() {
    initVariables();
    initTexture();
    initSprite();
    initAnimation();
    initPhysics();
}

Player::~Player() {
}

const bool& Player::getAnimSwitch() {
    bool anim_switch = animSwitch;

    if (animSwitch)
        animSwitch = false;
    return anim_switch;
}

const sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}

void Player::resetVelocityY() {
    velocity.y = 0;
}

void Player::initVariables() {
    animState = IDLE;
}

void Player::initTexture() {
    if (!textureSheet.loadFromFile("Textures/kirby_downsize.png"))
        std::cout << "ERROR::PLAYER::Couldn't load player texture!" << std::endl;
}

void Player::initSprite() {
    sprite.setTexture(textureSheet);
    //currentFrame = sf::IntRect(0, 0, 34, 35);
    currentFrame = sf::IntRect(0, 0, 32, 30);
    sprite.setTextureRect(currentFrame);
    sprite.setScale(10, 10);
}

void Player::initAnimation() {
    animationTimer.restart();
    animSwitch = true;
}

void Player::initPhysics() {
    maxVelocity = 10;
    minVelocity = 1;
    acceleration = 3;
    drag = 0.98;
    gravity = 0.8;
    maxGravity = 4;
}

void Player::update() {
    updatePlayer();
    updateAnimation();
    updatePhysics();
}

void Player::updatePlayer() {
    animState = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        move(-5, 0);
        animState = MOVING_LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        move(5, 0);
        animState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        move(0, -5);
        animState = JUMPING;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        move(0, 5);
        animState = FALLING;
    }
}
 
void Player::updateAnimation() {
    if (animState == IDLE) {  
        if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimSwitch()) {
            currentFrame.top = 0;
            currentFrame.left += 30;
            if (currentFrame.left >= 87)
                currentFrame.left = 0;
            animationTimer.restart();
            sprite.setTextureRect(currentFrame);
        }
    }
    else if (animState == MOVING_RIGHT) {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch()) {
            currentFrame.top = 90;
            currentFrame.left += 31;
            if (currentFrame.left >= 240)
                currentFrame.left = 0;
            animationTimer.restart();
            sprite.setTextureRect(currentFrame);
        }
        
        sprite.setScale(10, 10);
        sprite.setOrigin(0, 0);
    }
    else if (animState == MOVING_LEFT) {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch()) {
            currentFrame.top = 90;
            currentFrame.left += 31;
            if (currentFrame.left >= 240)
                currentFrame.left = 0;
            animationTimer.restart();
            sprite.setTextureRect(currentFrame);
        }
           
        sprite.setScale(-10, 10);
        sprite.setOrigin(sprite.getGlobalBounds().width/10, 0);
    }
    else 
        animationTimer.restart();
}

void Player::resetAnimationTimer() {
    animationTimer.restart();
    animSwitch = true;
}

void Player::updatePhysics() {
    //Gravity
    velocity.y += 2 * gravity;

    if (std::abs(velocity.x) > maxGravity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        velocity.y = maxGravity * ((velocity.y < 0) ? -1 : 1);
    }

    //Drag, lowers velocity value by 0.98 over time
    velocity *= drag;

    //Limit drag, basically once you reach a certain
    //minimum velocity, you stop moving
    if (std::abs(velocity.x) < minVelocity)
        velocity.x = 0;
    if (std::abs(velocity.y) < minVelocity)
        velocity.y = 0;

    sprite.move(velocity);
}

void Player::move(const float dir_x, const float dir_y) {
    //Acceleration
    velocity.x += dir_x * acceleration;
    //velocity.y += dir_y * acceleration; //not really used, we use gravity
    velocity.y = dir_y * acceleration;

    //Limit velocity/acceleration
    if (std::abs(velocity.x) > maxVelocity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        velocity.x = maxVelocity * ((velocity.x < 0) ? -1 : 1);
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(sprite);

    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(4);
    circle.setPosition(sprite.getPosition());
    target.draw(circle);
}
