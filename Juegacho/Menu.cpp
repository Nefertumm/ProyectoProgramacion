#include "Menu.hpp"
#include <iostream>
#include "ZonaBoss.hpp"



Menu::Menu(Game* game, RenderWindow* wnd): Escena(game, wnd) 
{
	if(!_fuente.loadFromFile("resources/Equestria.otf")) 
		std::cerr << "No se encontro la fuente" << std::endl;
	
	if (!_music.openFromFile("resources/menu.ogg"))
		std::cerr << "No se encontro el archivo de audio" << std::endl;
	
	_music.setVolume(100);
	_music.setLoop(true);
	_music.play();
	
	_mensajeTitulo.setFont(_fuente);
	_mensajeTitulo.setString("Injusticia hecha juego");
	_mensajeTitulo.setCharacterSize(62);
	_mensajeTitulo.setColor(Color::White);
	_mensajeTitulo.setOrigin(_mensajeTitulo.getGlobalBounds().width/2.0f, _mensajeTitulo.getGlobalBounds().height/2.0f);
	_mensajeTitulo.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/4.0f);
	
	_mensajeMenu.setFont(_fuente);
	_mensajeMenu.setString("Presione la tecla F(sqrt(169)) para empezar");
	_mensajeMenu.setCharacterSize(32);
	_mensajeMenu.setColor(Color::Red);
	_mensajeMenu.setOrigin(_mensajeMenu.getGlobalBounds().width/2.0f, _mensajeMenu.getGlobalBounds().height/2.0f);
	_mensajeMenu.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.0f);
	
}

Menu::~Menu() {
	
}

void Menu::Dibujar() 
{ 
	_wnd->clear(Color::Black);
	_wnd->draw(_mensajeTitulo);
	_wnd->draw(_mensajeMenu);
	
	_wnd->display();
}

void Menu::Actualizar(float dt) 
{
	if ((Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::Num3)) ||
		(Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::Numpad1) && Keyboard::isKeyPressed(Keyboard::Numpad3))) // Huevada in coming...
		_game->CambiarEscena(new ZonaBoss(_game, _wnd));
}

void Menu::ProcesarEventos() 
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		if (e.type == Event::Closed)
			_wnd->close();
	}
}

void Menu::ProcesarColisiones() { }



