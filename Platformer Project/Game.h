#include "Player.h"

class Game {
public:
	Game();
	~Game();

	//Functions
	void updatePlayer();
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;

protected:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	
	void initWindow();
	void initPlayer();
};

