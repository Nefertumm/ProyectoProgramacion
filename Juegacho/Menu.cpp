#include "Menu.hpp"
#include <iostream>
#include "ZonaBoss.hpp"
#include "EscenaPuntuacion.hpp"
#include "Controles.hpp"


Menu::Menu(Game* game, RenderWindow* wnd): Escena(game, wnd) 
{
	if(!_fuente.loadFromFile("resources/Equestria.otf")) 
		std::cerr << "No se encontro la fuente del menu" << std::endl;
	
	if (!_music.openFromFile("resources/menu.ogg"))
		std::cerr << "No se encontro el archivo de audio del menu" << std::endl;
	
	_music.setVolume(70);
	_music.setLoop(true);
	_music.play();
	
	_mensajeTitulo.setFont(_fuente);
	_mensajeTitulo.setString("Injusticia hecha juego");
	_mensajeTitulo.setCharacterSize(62);
	_mensajeTitulo.setFillColor(Color::White);
	_mensajeTitulo.setOrigin(_mensajeTitulo.getGlobalBounds().width/2.0f, _mensajeTitulo.getGlobalBounds().height/2.0f);
	_mensajeTitulo.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/4.0f);
	
	_mensajeMenu.setFont(_fuente);
	_mensajeMenu.setString("Presione la tecla F(sqrt(169)) para empezar");
	_mensajeMenu.setCharacterSize(32);
	_mensajeMenu.setFillColor(Color::Red);
	_mensajeMenu.setOrigin(_mensajeMenu.getGlobalBounds().width/2.0f, _mensajeMenu.getGlobalBounds().height/2.0f);
	_mensajeMenu.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.0f);
	
	_mensajeScore.setFont(_fuente);
	_mensajeScore.setString("Presione la tecla X para ver las puntuaciones");
	_mensajeScore.setCharacterSize(26);
	_mensajeScore.setFillColor(Color::Red);
	_mensajeScore.setOrigin(_mensajeScore.getGlobalBounds().width/2.0f, _mensajeScore.getGlobalBounds().height/2.0f);
	_mensajeScore.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.8f);
	
	mensajeControles.setFont(_fuente);
	mensajeControles.setString("Presione la tecla C para ver los controles");
	mensajeControles.setCharacterSize(26);
	mensajeControles.setFillColor(Color::Red);
	mensajeControles.setOrigin(mensajeControles.getGlobalBounds().width/2.0f, mensajeControles.getGlobalBounds().height/2.0f);
	mensajeControles.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.6f);
	
	_mensajeSalir.setFont(_fuente);
	_mensajeSalir.setString("Presione la tecla Escape para salir");
	_mensajeSalir.setCharacterSize(26);
	_mensajeSalir.setFillColor(Color::White);
	_mensajeSalir.setOrigin(_mensajeSalir.getGlobalBounds().width/2.0f, _mensajeSalir.getGlobalBounds().height/2.0f);
	_mensajeSalir.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.4f);
	
}

Menu::~Menu() { }

void Menu::Dibujar() 
{ 
	_wnd->clear(Color::Black);
	_wnd->draw(_mensajeTitulo);
	_wnd->draw(_mensajeMenu);
	_wnd->draw(_mensajeScore);
	_wnd->draw(_mensajeSalir);
	_wnd->draw(mensajeControles);
	
	_wnd->display();
}

void Menu::Actualizar(float dt) 
{
	if ((Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::Num3)) ||
		(Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::Numpad1) && Keyboard::isKeyPressed(Keyboard::Numpad3))) // Huevada in coming...
		_game->CambiarEscena(new ZonaBoss(_game, _wnd));
	if (Keyboard::isKeyPressed(Keyboard::C))
		_game->CambiarEscena(new Controles(_game, _wnd));
	if (Keyboard::isKeyPressed(Keyboard::X))
		_game->CambiarEscena(new EscenaPuntuacion(_game, _wnd));
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		_wnd->close();
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



