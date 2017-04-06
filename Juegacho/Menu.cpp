#include "Menu.hpp"
#include <iostream>


Menu::Menu(Game* game, RenderWindow* wnd): Escena(game, wnd) 
{
	if(!_fuente.loadFromFile("../resources/Equestria.otf")) 
		cerr<<"No se encontro la fuente"<<endl;
	
	_mensajeTitulo.setFont(_fuente);
	_mensajeTitulo.setString("Injusticia hecha juego");
	_mensajeTitulo.setCharacterSize(32);
	_mensajeTitulo.setColor(Color::White);
	_mensajeTitulo.setOrigin(_mensajeTitulo.getGlobalBounds().width/2.0f, _mensajeTitulo.getGlobalBounds().height/2.0f);
	_mensajeTitulo.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/4.0f);
	
	_mensajeMenu.setFont(_fuente);
	_mensajeMenu.setString("Presione la tecla F(sqrt(169)) para empezar");
	_mensajeMenu.setCharacterSize(22);
	_mensajeMenu.setColor(Color::Red);
	_mensajeMenu.setOrigin(_mensajeMenu.getGlobalBounds().width/2.0f, _mensajeMenu.getGlobalBounds().height/2.0f);
	_mensajeMenu.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.0f);
}

Menu::~Menu() {
	
}

