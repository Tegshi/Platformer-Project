#include "stdafx.h"
#include "Game.h"

//Constructor
Game::Game() {
	this->initWindow();
	this->initPlayer();
}

//destructor
Game::~Game() {
	delete this->player;
}

//Creates the game window
void Game::initWindow() {
	this->window.create(sf::VideoMode(2000, 1200), "Broken", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
}

//creates a player object
void Game::initPlayer() {
	this->player = new Player();
}

//returns the current window
const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}

//updates the player with a player object
void Game::updatePlayer() {
	this->player->update();
}

void Game::updateCollision() {
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > 
		this->window.getSize().y) {

		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x, this->window.getSize().y - 
			this->player->getGlobalBounds().height);
	}
}

void Game::update() {
	//Polling window events
	while (this->window.pollEvent(this->ev)) {
		//if the close button is pressed, the window closes
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		//if a key is pressed and it's the Esc key, the window closes
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();


		//fixes animation timer
		if (this->ev.type == sf::Event::KeyReleased && 
			(this->ev.key.code == sf::Keyboard::Left ||
				this->ev.key.code == sf::Keyboard::Up || 
				this->ev.key.code == sf::Keyboard::Right || 
				this->ev.key.code == sf::Keyboard::Down)) {
			this->player->resetAnimationTimer();
		}
	}

	//updates player
	this->updatePlayer();

	this->updateCollision();
}

void Game::render() {
	//clear the window, sf::Color::____ to set bg color
	this->window.clear();

	//Rendering
	this->renderPlayer();

	//draw the new window
	this->window.display();
}

void Game::renderPlayer() {
	this->player->render(this->window);
}
