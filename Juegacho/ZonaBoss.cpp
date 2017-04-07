#include "ZonaBoss.hpp"

ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd) 
{
	
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
