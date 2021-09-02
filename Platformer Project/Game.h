#include "Player.h"

class Game {
public:
	Game();
	~Game();

	//Functions
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

protected:
	sf::RenderWindow window;
	sf::Event ev;
	sf::Sprite bgSprite;
	sf::Texture background;

	//player object
	Player* player;

	//initialization
	void initWindow();
	void initPlayer();
	void initBackground();
	void initbgSprite();
};

