#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game()
{
	wnd = new RenderWindow(sf::VideoMode(800,600), "Injusticia hecha juego"/*, sf::Style::Titlebar|sf::Style::Close*/);
	wnd->setFramerateLimit(60);
	
	_escenaAnterior = nullptr;
	_escenaActual = new Menu(this, wnd);
	
	// Si el archivo no está creado, crearlo.
	ifstream archi("puntaje.dat", ios::binary);
	if (!archi.is_open())
	{
		cerr << "No se encuentra el archivo puntaje.dat" << endl;
		ofstream archiCrear("puntaje.dat", ios::binary|ios::trunc);
		archiCrear.close();
		return;
	}
	archi.close();
}

void Game::run()
{
	float deltaTime = 0.0f;
	while (wnd->isOpen())
	{
		deltaTime = _clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		
		_escenaActual->ProcesarEventos();
		_escenaActual->Actualizar(deltaTime);
		_escenaActual->ProcesarColisiones();
		_escenaActual->Dibujar();
		delete _escenaAnterior; _escenaAnterior = nullptr;
	}
}

Game::~Game() 
{
	delete wnd;
	delete _escenaActual;
}

void Game::CambiarEscena(Escena* nuevaEscena)
{
//	if (_escenaActual != nullptr)
//	  	delete _escenaActual;
	_escenaAnterior = _escenaActual;
	_escenaActual = nuevaEscena;
}
