#include "ZonaBoss.hpp"
#include <iostream>

ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd) 
{
	if (!_ambiente.openFromFile("resources/boss.ogg"))
		std::cerr << "No se pudo cargar la musica del boss." << std::endl;
	
	_ambiente.setVolume(0); // cambiar a 100 cuando ya este hecho.
	_ambiente.setLoop(true);
	_ambiente.play();
}

ZonaBoss::~ZonaBoss() { }

void ZonaBoss::Dibujar() 
{
	_wnd->clear(sf::Color::White);
	_jugador.Dibujar(_wnd);
	_wnd->display();
}

void ZonaBoss::ProcesarColisiones()
{
	
}

void ZonaBoss::ProcesarEventos()
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		switch (e.type)
		{
			case sf::Event::Closed:
				_wnd->close();
				break;
			default:
				break;
		}
	}
}

void ZonaBoss::Reiniciar()
{
	
}

void ZonaBoss::GameOver()
{
	
}
