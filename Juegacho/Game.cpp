#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Menu.hpp"


Game::Game()
{
	mWindow = new RenderWindow(sf::VideoMode(800,600), "Injusticia hecha juego");
	
	_escenaActual = new Menu(this, mWindow);
}

void Game::run()
{
	_clock.restart();
	
	while (mWindow->isOpen())
	{
		_escenaActual->ProcesarEventos();
		_escenaActual->Actualizar(_clock.restart().asSeconds());
		_escenaActual->ProcesarColisiones();
		_escenaActual->Dibujar();
	}
}

Game::~Game() 
{
	delete mWindow;
	if (_escenaActual != nullptr)
		delete _escenaActual;
}
