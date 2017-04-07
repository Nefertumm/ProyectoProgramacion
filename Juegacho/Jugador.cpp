#include "Jugador.hpp"
#include <iostream>
#include <cmath>

Jugador::Jugador() : _suelo(550), _velGravedad(981.f), _isJumping(false), _dSalto(300.0f) {
	if (!_texture.loadFromFile("resources/idle.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	
	_sprite.setTexture(_texture);
	//_sprite.setScale(1.5f, 1.5f);
	_sprite.setPosition(0.0f, _suelo);
	
	_velocidad = { 0.f, 0.f };
}

Jugador::~Jugador() {
	
}

void Jugador::Dibujar(sf::RenderWindow* wnd)
{
	_wndSize = wnd->getSize();
	_sprite.setScale((float)(_wndSize.x / 451.f),(float)(_wndSize.y / 338.4f)); // bastante acertado
	//std::cout << _sprite.getScale().x << " " << _sprite.getScale().y << std::endl; // simplemente para ver la escala de la textura
	wnd->draw(_sprite);
}

void Jugador::Actualizar(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_velocidad.x = -300.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_velocidad.x = 300.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)/* && !_isJumping*/) // es una pija
	{
		_isJumping = true;
		_velocidad.y = (float)-sqrt(2.0f * _velGravedad * _dSalto);
	}
	if (_sprite.getPosition().y < _suelo && !_isJumping)
		_velocidad.y += _velGravedad; // Falta hacer que se mueva por FPS. 

	
	_sprite.move(_velocidad * dt);

	
	
	if (_sprite.getPosition().x < 0.f)
		_sprite.setPosition( sf::Vector2f(0.f, _sprite.getPosition().y) );
	else if (_sprite.getPosition().x > (800 - _sprite.getTexture()->getSize().x * 1.7f))
		_sprite.setPosition( sf::Vector2f(800 - _sprite.getTexture()->getSize().x * 1.7f, _sprite.getPosition().y) );
	if (_sprite.getPosition().y > _suelo)
		_sprite.setPosition(_sprite.getPosition().x, _suelo);
	_velocidad = { 0.f, 0.f };
	
}

sf::FloatRect Jugador::Bounds()
{
	return _sprite.getGlobalBounds();
}
