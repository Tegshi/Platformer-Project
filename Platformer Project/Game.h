#include "stdafx.h"
class Game
{
public:
	Game();
	~Game();

	//Functions
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;

protected:
	sf::RenderWindow window;
	
	void initWindow();
};

