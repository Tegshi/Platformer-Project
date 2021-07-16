#include "stdafx.h"
#include "Game.h"

//Constructor
Game::Game() {
	this->initWindow();
}

Game::~Game() {

}

//Creates the game window
void Game::initWindow() {
	this->window.create(sf::VideoMode(800, 600), "Ghetto", sf::Style::Close | sf::Style::Titlebar);
}


void Game::update() {
	std::cout << "Test" << "\n";
}

void Game::render() {

}

const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}
