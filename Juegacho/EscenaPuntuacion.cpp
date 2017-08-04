#include "EscenaPuntuacion.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include <iostream>
#include <sstream>

EscenaPuntuacion::EscenaPuntuacion(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd) 
{
	if (!_fuente.loadFromFile("resources/Equestria.otf"))
		std::cerr << "No se pudo cargar la fuente de la tabla de puntuaciones" << std::endl;	
	
	_tituloPuntuaciones.setFont(_fuente);
	_tituloPuntuaciones.setString("Tabla de puntuaciones");
	_tituloPuntuaciones.setCharacterSize(76);
	_tituloPuntuaciones.setFillColor(Color::Blue);
	_tituloPuntuaciones.setOrigin(_tituloPuntuaciones.getGlobalBounds().width/2.0f, _tituloPuntuaciones.getGlobalBounds().height/2.0f);
	_tituloPuntuaciones.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/8.0f);
	
	// Esto no esta levantando bien los datos del archivo por algun motivo...
	std::stringstream ss;
	for(int i=0;i<_game->manPun.cantPuntajes();i++) 
	{
		const Puntuacion &punt = _game->manPun.verPuntaje(i);
		std::cout << punt._nombre << " " << punt._puntos << std::endl;
		ss << punt._nombre << "      -      " << punt._puntos << std::endl;
	}
	
	std::string str = ss.str();
	
	_textPuntuaciones.setFont(_fuente);
	_textPuntuaciones.setString(str);
	_textPuntuaciones.setCharacterSize(32);
	_textPuntuaciones.setFillColor(Color::Red);
	_textPuntuaciones.setOrigin(_textPuntuaciones.getGlobalBounds().width/2.0f, _textPuntuaciones.getGlobalBounds().height/2.0f);
	_textPuntuaciones.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.f);
	
	_volverMenu.setFont(_fuente);
	_volverMenu.setString("Presione la tecla Z nuevamente para volver al menu");
	_volverMenu.setCharacterSize(32);
	_volverMenu.setFillColor(Color::Red);
	_volverMenu.setOrigin(_volverMenu.getGlobalBounds().width/2.0f, _volverMenu.getGlobalBounds().height/2.0f);
	_volverMenu.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.1f);
}

EscenaPuntuacion::~EscenaPuntuacion() { }

void EscenaPuntuacion::Dibujar() 
{
	_wnd->clear(Color::Black);
	_wnd->draw(_volverMenu);
	_wnd->draw(_textPuntuaciones);
	_wnd->draw(_tituloPuntuaciones);
	
	_wnd->display();
}
void EscenaPuntuacion::Actualizar(float dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_game->CambiarEscena(new Menu(_game, _wnd));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_wnd->close();
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
