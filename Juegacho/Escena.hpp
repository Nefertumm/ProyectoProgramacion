#ifndef ESCENA_HPP
#define ESCENA_HPP
#include "Game.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

class Game;

class Escena 
{
protected:
	Game* _game;
	RenderWindow* _wnd;
	
	void Reiniciar();
public:
	Escena(Game* game, RenderWindow* wnd);
	virtual ~Escena();
	
	virtual void Dibujar() = 0; 
	virtual void Actualizar(float dt) = 0;
	virtual void ProcesarColisiones() = 0;
	virtual void ProcesarEventos() = 0;
	
};

#endif

