#include "Movement.h"
//Player class, contains player information and rendering
class Player {
public:
    Player();
    ~Player();

    void update();
    void render(sf::RenderTarget& target);
    void updatePlayer();

protected:
    sf::Sprite sprite; //"shape" of player
    sf::Texture textureSheet; //"image" of player

    Movement* movement;

    //initialization
    void initTexture();
    void initSprite();
    void initMovement();
};

