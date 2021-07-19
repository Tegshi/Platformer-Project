#include "Movement.h"
//Player class, contains player information and rendering

class Player {
public:
    Player();
    ~Player();

    void update();
    void render(sf::RenderTarget& target);
    void updatePlayer();
    void updateAnimation();

protected:
    sf::Sprite sprite; //"shape" of player
    sf::Texture textureSheet; //"image" of player

    //Animation
    sf::IntRect currentFrame;
    sf::Clock animationTimer;
    int animState;

    Movement* movement;

    //initialization
    void initVariables();

    void initTexture();
    void initSprite();
    void initMovement();
    void initAnimation();
};

