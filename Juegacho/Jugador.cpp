#include "Jugador.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Jugador::Jugador() : _velGravedad(1800.f), _isJumping(false), _dSalto(150.0f), _movementSpeed(300.f)
{	
	if (!_texture.loadFromFile("resources/jugador.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0.f,0.f,49.f,49.f));
	
	_sprite.setPosition(0.0f, _suelo);
	
	mIzquierda = false;
	anim = new Animaciones(&_texture, sf::Vector2u(8, 3), 0.1f);
	
	_velocidad = { 0.f, 0.f };
}

Jugador::~Jugador() 
{
	delete anim;
}

void Jugador::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(_sprite);
}

void Jugador::setVelocity(sf::Vector2f vel)
{
	_velocidad = vel;
}

void Jugador::Actualizar(float dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_velocidad.x = -_movementSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_velocidad.x = _movementSpeed;
	else
		_velocidad.x = 0;
	
	if (_velocidad.x == 0)
		fila = 0;
	else
	{
		fila = 1;
		
		if (_velocidad.x < 0.0f)
			mIzquierda = true;
		else
			mIzquierda = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_isJumping)
	{
		_isJumping = true;
		_velocidad.y = (float)-sqrtf(2.0f * _velGravedad * _dSalto);
		_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y-1);
	}
	

	if(_isJumping)
	{
		_velocidad.y += dt * _velGravedad;
		if (_sprite.getPosition().y >= _suelo)
		{
			_sprite.setPosition(_sprite.getPosition().x, _suelo);
			_isJumping = false;
			_velocidad.y = 0;
		}
	}
	
	anim->Actualizar(fila, dt, mIzquierda);
	_sprite.setTextureRect(anim->uvRect);
	_sprite.move(_velocidad * dt);
	
	mantenerJugadorEnPantalla();
}

sf::FloatRect Jugador::Bounds()
{
	return _sprite.getGlobalBounds();
}

void Jugador::modificarPos(sf::Vector2f v)
{
	_sprite.move(v);
}

void Jugador::mantenerJugadorEnPantalla() 
{
	if (_sprite.getPosition().x <= 0.f)
		_sprite.setPosition( sf::Vector2f(0.f, _sprite.getPosition().y) );
	else if (_sprite.getPosition().x > (740 - _sprite.getTextureRect().width/2))
		_sprite.setPosition( sf::Vector2f(740 - _sprite.getTextureRect().width/2, _sprite.getPosition().y) );
}

void Jugador::setJumping(bool jump)
{
	_isJumping = jump;
}
