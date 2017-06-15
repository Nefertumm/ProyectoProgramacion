#include "EscenaPuntuacion.hpp"
#include "Menu.hpp"
#include <iostream>

EscenaPuntuacion::EscenaPuntuacion(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd) 
{
	if (!_fuente.loadFromFile("resources/Equestria.otf"))
		std::cerr << "No se pudo cargar la fuente de la tabla de puntuaciones" << std::endl;
	
	_volverMenu.setFont(_fuente);
	_volverMenu.setString("Presione la tecla Z nuevamente para volver al menu");
	_volverMenu.setCharacterSize(26);
	_volverMenu.setColor(Color::Red);
	_volverMenu.setOrigin(_volverMenu.getGlobalBounds().width/2.0f, _volverMenu.getGlobalBounds().height/2.0f);
	_volverMenu.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.1f);
	
}

EscenaPuntuacion::~EscenaPuntuacion() 
{
	
}

void EscenaPuntuacion::Dibujar() 
{
	_wnd->clear(Color::Black);
	_wnd->draw(_volverMenu);
	
	_wnd->display();
}
void EscenaPuntuacion::Actualizar(float dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_game->CambiarEscena(new Menu(_game, _wnd));
}

void EscenaPuntuacion::ProcesarEventos() 
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		if (e.type == Event::Closed)
			_wnd->close();
	}
}
