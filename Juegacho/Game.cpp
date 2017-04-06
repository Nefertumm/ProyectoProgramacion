#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Menu.hpp"


Game::Game()
{
	wnd = new RenderWindow(sf::VideoMode(800,600), "Injusticia hecha juego");
	
	_escenaActual = new Menu(this, wnd);
}

void Game::run()
{
	_clock.restart();
	
	while (wnd->isOpen())
	{
		_escenaActual->ProcesarEventos();
		_escenaActual->Actualizar(_clock.restart().asSeconds());
		_escenaActual->ProcesarColisiones();
		_escenaActual->Dibujar();
	}
}

Game::~Game() 
{
	delete wnd;
	if (_escenaActual != nullptr)
		delete _escenaActual;
}

void Game::CambiarEscena(Escena* nuevaEscena)
{
	if (_escenaActual != nullptr)
		delete _escenaActual;
	
	_escenaActual = nuevaEscena;
}
