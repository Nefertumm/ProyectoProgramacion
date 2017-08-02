#ifndef ESCENAGAMEOVER_HPP
#define ESCENAGAMEOVER_HPP

#include "Game.hpp"
#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resources/InputBox.h"
#include "ManejoPuntuacion.hpp"

class EscenaGameOver : public Escena
{
protected:
	sf::Font _fuente;
	sf::Text _gameOver;
	sf::Text _ingresarTexto;
	sf::Music gameOver;
	InputText _nombre;
	Puntuacion _puntJugador;
	
public:
	EscenaGameOver(Game* game, sf::RenderWindow* wnd, int score);
	~EscenaGameOver();
	
	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override { }
	void ProcesarEventos() override;
};

#endif

