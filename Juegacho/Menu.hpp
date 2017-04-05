#ifndef MENU_H
#define MENU_H
#include "Escena.hpp"
#include <SFML/Graphics.hpp>


class Menu : public Escena {

protected:
	sf::Font _fuente;
	sf::Text mensajeTitulo;
	sf::Text mensajeMenu;
	
public:
	Menu(Game* game, RenderWindow* wnd);
	~Menu();
	
	void Dibujar();
	void Actualizar(float dt);
	void ProcesarColisiones();
	void ProcesarEventos();
};

#endif

