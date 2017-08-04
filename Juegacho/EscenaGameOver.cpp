#include "EscenaGameOver.hpp"
//#include "resources/InputBox.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"
#include <fstream>
using namespace std;

EscenaGameOver::EscenaGameOver(Game* game, sf::RenderWindow* wnd, int score) : Escena(game, wnd), _nombre(_fuente, 62, sf::Color::Blue)
{
	if (!_fuente.loadFromFile("resources/Equestria.otf"))
		cerr << "No se encontro la fuente de la escena GameOver" << endl;
	if (!gameOver.openFromFile("resources/GameOver.ogg"))
		cerr << "No se encontro el sonido de la escena GameOver" << endl;
	
	_puntJugador._puntos = score;
	gameOver.setVolume(100);
	gameOver.play();
	
	_nombre.setPosition(400,300);
	_nombre.setMaxChars(15); 
	_nombre.setSingleWord(true); 
	
	_gameOver.setFont(_fuente);
	_gameOver.setString("GAME OVER");
	_gameOver.setCharacterSize(62);
	_gameOver.setFillColor(Color::Red);
	_gameOver.setOrigin(_gameOver.getGlobalBounds().width/2.0f, _gameOver.getGlobalBounds().height/2.0f);
	_gameOver.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/4.0f);
	
	_ingresarTexto.setFont(_fuente);
	_ingresarTexto.setString("Ingrese su nombre: ");
	_ingresarTexto.setCharacterSize(48);
	_ingresarTexto.setFillColor(Color::Blue);
	_ingresarTexto.setOrigin(_ingresarTexto.getGlobalBounds().width/2.0f, _ingresarTexto.getGlobalBounds().height/2.0f);
	_ingresarTexto.setPosition(wnd->getSize().x/4.0f, wnd->getSize().y/2.5f);
}

EscenaGameOver::~EscenaGameOver() { }


void EscenaGameOver::Dibujar() 
{
	_wnd->clear(Color::Black);
	_nombre.update();
	_wnd->draw(_gameOver);
	_wnd->draw(_ingresarTexto);
	_wnd->draw(_nombre);
	
	_wnd->display();
}
void EscenaGameOver::Actualizar(float dt) { }

void EscenaGameOver::ProcesarEventos()
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		if (e.type == Event::Closed)
			_wnd->close();
		else if (e.type==sf::Event::KeyPressed && e.key.code==sf::Keyboard::Return) { 
			string string_ingresado = _nombre.getValue(); 
			if (string_ingresado.length() < 1)
				_puntJugador._nombre = "Player";
			else 
				_puntJugador._nombre = string_ingresado;
			
			_game->manPun.registrarPuntuacion(_puntJugador);
			
			_game->CambiarEscena(new Menu(_game, _wnd));
		} else _nombre.processEvent(e);
	}
}

