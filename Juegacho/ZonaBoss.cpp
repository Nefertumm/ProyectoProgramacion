#include "ZonaBoss.hpp"

ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd) 
{
	
}

ZonaBoss::~ZonaBoss() { }

void ZonaBoss::Dibujar() 
{
	_wnd->clear();
	_jugador.Dibujar(_wnd);
	_wnd->display();
}

void ZonaBoss::Actualizar(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
		_jugador.Izquierda();
	if (Keyboard::isKeyPressed(Keyboard::Right))
		_jugador.Derecha();
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		_jugador.Saltar();
		_jugador.estaSaltando(true);
	}
	
	_jugador.Actualizar(dt);
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
			
			case sf::Event::KeyReleased:
				_jugador.estaSaltando(false);
		}
	}
}

void ZonaBoss::Reiniciar()
{
	
}

void ZonaBoss::GameOver()
{
	
}
