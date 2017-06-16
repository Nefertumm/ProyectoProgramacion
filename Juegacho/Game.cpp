#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game()
{
	wnd = new RenderWindow(sf::VideoMode(800,600), "Injusticia hecha juego", sf::Style::Titlebar|sf::Style::Close);
	wnd->setFramerateLimit(60);
	
	_escenaActual = new Menu(this, wnd);
	
	// Si el archivo no está creado, crearlo.
	ifstream archi("puntaje.dat", ios::binary);
	if (!archi.is_open())
	{
		cerr << "No se encuentra el archivo puntaje.dat" << endl;
		ofstream archiCrear("puntaje.dat", ios::binary|ios::trunc);
		return;
	}
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
