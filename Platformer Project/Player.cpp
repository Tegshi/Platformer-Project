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
    spriteScale = 4;
    animState = IDLE;
    canJump = true;
}

void Player::initTexture() {
    if (!textureSheet.loadFromFile("Textures/kirby_downsize.png"))
        std::cout << "ERROR::PLAYER::Couldn't load player texture!" << std::endl;
}

void Player::initSprite() {
    sprite.setTexture(textureSheet);
    currentFrame = sf::IntRect(0, 0, 32, 30);
    sprite.setTextureRect(currentFrame);
    sprite.setScale(spriteScale, spriteScale);
}

void Player::initAnimation() {
    animationTimer.restart();
    animSwitch = true;
}

void Player::initPhysics() {
    maxVelocity = 7;
    minVelocity = 1;
    acceleration = 2;
    drag = 0.98;
    gravity = 0.6;
    maxGravity = 30;
    jumpHeight = 4;
}

void Player::update() {
    updatePlayer();
    updateAnimation();
    updatePhysics();
}

void Player::updatePlayer() {
    animState = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        animState = MOVING_LEFT;
        move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        animState = MOVING_RIGHT;
        move(5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump) {
        animState = JUMPING;
        move(0, -5);
        canJump = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        animState = FALLING;
        move(0, 5);
    }
}

bool& Player::getJump() {
    return canJump;
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
        
        sprite.setScale(spriteScale, spriteScale);
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
           
        sprite.setScale(-spriteScale, spriteScale);
        sprite.setOrigin(sprite.getGlobalBounds().width/spriteScale, 0);
    }
    else 
        animationTimer.restart();
}

void Player::resetAnimationTimer() {
    animationTimer.restart();
    animSwitch = true;
}

void Player::updatePhysics() {

    if (std::abs(velocity.x) > maxGravity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        velocity.y = maxGravity * ((velocity.y < 0) ? -1 : 1);
    }

    //Drag, lowers velocity value by 0.98 over time
    velocity *= drag;

    //if not moving at least minVelocity, sprite won't move
    //also simulates gravity
    if (std::abs(velocity.x) < minVelocity)
        velocity.x = 0;
    else if (std::abs(velocity.y) < minVelocity)
        velocity.y = 0;

    //Gravity
    velocity.y += 2 * gravity;

    sprite.move(velocity);
}

void Player::move(const float dir_x, const float dir_y) {
    //Acceleration, left and right
    velocity.x += dir_x * acceleration;

    //Jumping
    if (animState == JUMPING)
        velocity.y = -sqrt(abs(dir_y) * (gravity*60) * jumpHeight);

    //Limit velocity/acceleration
    if (std::abs(velocity.x) > maxVelocity) {
        //conditional operator: if velocity x is < 0, then it is multiplied by -1
        //in order to keep the velocity in the proper direction
        velocity.x = maxVelocity * ((velocity.x < 0) ? -1 : 1);
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(sprite);

    /* top left coordinate of player sprite
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(spriteScale);
    circle.setPosition(sprite.getPosition());
    target.draw(circle);
    */
}
