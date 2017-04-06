#include "Jugador.hpp"
#include <iostream>

Jugador::Jugador() : _suelo(550), _velGravedad(0.1f), _isJumping(false) {
	if (!_texture.loadFromFile("resources/idle.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	
	_sprite.setTexture(_texture);
	_sprite.setScale(1.5f, 1.5f);
	_sprite.setPosition(0.0f, _suelo);
	
	_direccion.x = 0.f;
	_direccion.y = 0.f;
	_velocidad = 200.f;
}

Jugador::~Jugador() {
	
}

void Jugador::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(_sprite);
}

void Jugador::Actualizar(float dt)
{
	_sprite.move(_direccion * _velocidad * dt);

	if (_sprite.getPosition().y < _suelo && _isJumping == false)
		_sprite.move( sf::Vector2f(0.f, _velGravedad) ); // Falta hacer que se mueva por FPS. 
	
	_direccion.x = 0;
	_direccion.y = 0;
}

sf::FloatRect Jugador::Bounds()
{
	return _sprite.getGlobalBounds();
}

void Jugador::Saltar()
{
	// @ToDo: Poner un limite a cuanto en x puede moverse.
	_direccion.y -= 1.0f; // El eje coordenado no está como pensabamos, ahora todo cuadra. Esta intercambiado el eje y, cuando va para abajo es + y para arriba es -
}

void Jugador::Izquierda()
{
	_direccion.x -= 1.0f;
}

void Jugador::Derecha()
{
	_direccion.x += 1.0f;
}
