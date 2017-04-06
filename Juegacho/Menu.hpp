#ifndef MENU_H
#define MENU_H
#include "Escena.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Menu : public Escena {

protected:
	sf::Font _fuente;
	sf::Text _mensajeTitulo;
	sf::Text _mensajeMenu;
	
public:
	Menu(Game* game, RenderWindow* wnd);
	~Menu();
	
	void Dibujar();
	void Actualizar(float dt);
	void ProcesarColisiones();
	void ProcesarEventos();
};

#endif

