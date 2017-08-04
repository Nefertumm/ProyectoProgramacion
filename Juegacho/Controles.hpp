#ifndef CONTROLES_HPP
#define CONTROLES_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Escena.hpp"

class Controles : public Escena 
{
protected:
	sf::Font fuente;
	sf::Text controles, up, left, right, freeze, god, volver;
public:
	Controles(Game* game, sf::RenderWindow* wnd);
	~Controles();

	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override;
	void ProcesarEventos() override;
};

#endif

