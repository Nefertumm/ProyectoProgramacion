#ifndef ESCENAPUNTUACION_HPP
#define ESCENAPUNTUACION_HPP

#include "Game.hpp"
#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class EscenaPuntuacion : public Escena
{

protected:
	sf::Font _fuente;
	sf::Text _volverMenu;
	sf::Text _textPuntuaciones;
	sf::Text _tituloPuntuaciones;
	std::vector<Puntuacion> _puntuaciones;
	
public:
	EscenaPuntuacion(Game* game, sf::RenderWindow* wnd);
	~EscenaPuntuacion();
	
	void Dibujar();
	void Actualizar(float dt);
	void ProcesarColisiones() { }
	void ProcesarEventos();
};

#endif
