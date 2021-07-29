#include "stdafx.h"
#include "Game.h"

//Constructor
Game::Game() {
	initWindow();
	initBackground();
	initbgSprite();
	initPlayer();

}

//destructor
Game::~Game() {
	delete player;
}

//Creates the game window
void Game::initWindow() {
	window.create(sf::VideoMode(1600, 900), "Broken", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(144);
}

//creates a player object
void Game::initPlayer() {
	player = new Player();
}

void Game::initBackground() {
	if (!background.loadFromFile("Textures/pixelbg.png"))
		std::cout << "ERROR::GAME::Couldn't load background texture!" << std::endl;
}

void Game::initbgSprite() {
	bgSprite.setTexture(background);
	sf::IntRect frame = sf::IntRect(0, 0, 1600, 900);
	bgSprite.setTextureRect(frame);
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

		player->getJump() = true;
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

	window.draw(bgSprite); //draw background
	renderPlayer(); //render player sprite

	//draw the new window
	window.display();
}

void Game::renderPlayer() {
	player->render(window);
}
