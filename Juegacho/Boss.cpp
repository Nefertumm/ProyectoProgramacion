#include "Boss.hpp"
#include <iostream>

Boss::Boss() 
{
	if (!_texture.loadFromFile("resources/boss.png"))
		std::cerr << "No se encontró la textura del boss." << std::endl;
	
	_sprite.setTexture(_texture);
}

Boss::~Boss() { }

void Boss::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(_sprite);
}

void Boss::Actualizar(float dt)
{
	
}
