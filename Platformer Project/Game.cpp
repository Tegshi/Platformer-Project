#include "stdafx.h"
#include "Game.h"

//Constructor
Game::Game() {
	initWindow();
	initPlayer();
}

//destructor
Game::~Game() {
	delete player;
}

//Creates the game window
void Game::initWindow() {
	window.create(sf::VideoMode(2000, 1200), "Broken", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(144);
}

//creates a player object
void Game::initPlayer() {
	player = new Player();
}

//returns the current window
const sf::RenderWindow& Game::getWindow() const {
	return window;
}

//updates the player with a player object
void Game::updatePlayer() {
	player->update();
}

void Game::updateCollision() {
	//Collision bottom of screen
	if (player->getPosition().y + player->getGlobalBounds().height > 
		window.getSize().y) {

		player->resetVelocityY();
		player->setPosition(
			player->getPosition().x, window.getSize().y - 
			player->getGlobalBounds().height);
	}
}

void Game::update() {
	//Polling window events
	while (window.pollEvent(ev)) {
		//if the close button is pressed, the window closes
		if (ev.type == sf::Event::Closed)
			window.close();
		//if a key is pressed and it's the Esc key, the window closes
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			window.close();


		//fixes animation timer
		if (ev.type == sf::Event::KeyReleased && 
			(ev.key.code == sf::Keyboard::Left ||
				ev.key.code == sf::Keyboard::Up || 
				ev.key.code == sf::Keyboard::Right || 
				ev.key.code == sf::Keyboard::Down)) {
			player->resetAnimationTimer();
		}
	}

	//updates player
	updatePlayer();

	updateCollision();
}

void Game::render() {
	//clear the window, sf::Color::____ to set bg color
	window.clear();

	//Rendering
	renderPlayer();

	//draw the new window
	window.display();
}

void Game::renderPlayer() {
	player->render(window);
}
