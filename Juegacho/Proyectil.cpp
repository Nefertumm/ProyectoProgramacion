#include "Proyectil.hpp"
#include <iostream>

Proyectil::Proyectil()
{
	if (!_texture.loadFromFile("resources/proyectil.png"))
		std::cerr << "No se pudo cargar la textura del proyectil" << std::endl;
	
	_sprite.setTexture(_texture);
	anim = new Animaciones(&_texture, sf::Vector2u(5, 1), 0.1f);
	
	_sprite.setPosition(150.f, 300.f);
}

Proyectil::~Proyectil() 
{
	delete anim;
}

void Proyectil::Actualizar(float dt)
{
	anim->Actualizar(0, dt);
	_sprite.setTextureRect(anim->uvRect);
}

void Proyectil::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(_sprite);
}
