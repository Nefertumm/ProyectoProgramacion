#ifndef ESCENAPUNTUACION_HPP
#define ESCENAPUNTUACION_HPP

#include "Game.hpp"
#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ManejoPuntuacion.hpp"

class EscenaPuntuacion : public Escena
{

protected:
	sf::Font _fuente;
	sf::Text _volverMenu;
	sf::Text _textPuntuaciones;
	sf::Text _tituloPuntuaciones;
	
public:
	EscenaPuntuacion(Game* game, sf::RenderWindow* wnd);
	~EscenaPuntuacion();
	
	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override { }
	void ProcesarEventos() override;
};

#endif

