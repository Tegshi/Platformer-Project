#include "stdafx.h"

class Player {
public:
    Player();
    ~Player();

    void update();
    void render(sf::RenderTarget& target);

protected:
    sf::Sprite sprite;
    sf::Texture textureSheet;

    void initSprite();
    void initTexture();
};

