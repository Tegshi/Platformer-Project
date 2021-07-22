#include "stdafx.h"
//Player class, contains player information and rendering

enum PLAYER_ANIMATION_STATES {IDLE, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Player {
public:
    Player();
    ~Player();

    //Accessors
    const bool& getAnimSwitch();
    const sf::Vector2f getPosition() const;
    const sf::FloatRect getGlobalBounds() const;

    //Modifiers
    void setPosition(const float x, const float y);
    void resetVelocityY();

    //Functions
    void update();
    void render(sf::RenderTarget& target);
    void updatePlayer();
    void updateAnimation();
    void resetAnimationTimer();
    void updatePhysics();
    void move(const float dir_x, const float dir_y); //not like SFML move functions

protected:
    sf::Sprite sprite; //"shape" of player
    sf::Texture textureSheet; //"image" of player

    //Animation
    sf::IntRect currentFrame;
    sf::Clock animationTimer;
    int animState;
    bool animSwitch;

    //Physics
    sf::Vector2f velocity;
    float maxVelocity;
    float minVelocity;
    float acceleration;
    float drag;
    float gravity;
    float maxGravity;

    //initialization
    void initVariables();
    void initTexture();
    void initSprite();
    void initAnimation();
    void initPhysics();
};

