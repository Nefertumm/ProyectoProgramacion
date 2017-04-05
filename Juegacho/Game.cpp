#include "Game.hpp"


Game::Game()
{
	mWindow = new RenderWindow(sf::VideoMode(800,600),"Proyecto Poo");
	
}

void Game::run()
{
	while(mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents 
{
	sf::Event evento;
	while(mWindow.pollEvent(evento))
	{
		
	}
};
