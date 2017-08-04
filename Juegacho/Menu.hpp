#ifndef MENU_HPP
#define MENU_HPP
#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Menu : public Escena 
{

protected:
	sf::Font _fuente;
	sf::Text _mensajeTitulo;
	sf::Text _mensajeMenu;
	sf::Text _mensajeScore;
	sf::Text _mensajeSalir;
	sf::Text mensajeControles;
	sf::Music _music;

	
public:
	Menu(Game* game, RenderWindow* wnd);
	~Menu();
	
	
	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override;
	void ProcesarEventos() override;
};

#endif

