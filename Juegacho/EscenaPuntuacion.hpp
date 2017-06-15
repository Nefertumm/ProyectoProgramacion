#ifndef ESCENAPUNTUACION_HPP
#define ESCENAPUNTUACION_HPP

#include "Game.hpp"
#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class EscenaPuntuacion : public Escena
{

protected:
	sf::Font _fuente;
	sf::Text _volverMenu;
	std::vector<sf::Text> _puntuaciones; // no estoy seguro.
	
public:
	EscenaPuntuacion(Game* game, sf::RenderWindow* wnd);
	~EscenaPuntuacion();
	
	void Dibujar();
	void Actualizar(float dt);
	void ProcesarColisiones() { }
	void ProcesarEventos();
	
};

#endif

