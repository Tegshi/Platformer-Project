#include "Player.h"

class Game {
public:
	Game();
	~Game();

	//Functions
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

protected:
	sf::RenderWindow window;
	sf::Event ev;

	//player object
	Player* player;

	//initialization
	void initWindow();
	void initPlayer();
};

