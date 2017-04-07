#ifndef ZONA_HPP
#define ZONA_HPP

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Nuestro
#include "Game.hpp"
#include "Escena.hpp"
#include "Jugador.hpp"


class ZonaBoss : public Escena 
{
protected:
	sf::Music _ambiente;
	
	Jugador _jugador;
	
public:
	ZonaBoss(Game* game, sf::RenderWindow* wnd);
	~ZonaBoss();
	
	void Reiniciar();
	
	void Dibujar();
	inline void Actualizar(float dt) { _jugador.Actualizar(dt); }
	void ProcesarColisiones();
	void ProcesarEventos();
	
	void GameOver();
};

#endif

