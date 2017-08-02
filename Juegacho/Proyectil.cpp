#include "Proyectil.hpp"
#include <iostream>

Proyectil::Proyectil()
{
	if (!texture.loadFromFile("resources/proyectil.png"))
		std::cerr << "No se pudo cargar la textura del proyectil" << std::endl;
	
	sprite.setTexture(texture);
	anim = new Animaciones(&texture, sf::Vector2u(5, 1), 0.1f);
	
	sprite.setScale(0.5f, 0.5f);
	
	velocidad = { 0.f, 0.f };
}

Proyectil::~Proyectil() 
{
	delete anim;
}

void Proyectil::Actualizar(float dt)
{
	sprite.move(velocidad * dt);
	
	anim->Actualizar(0, dt);
	sprite.setTextureRect(anim->uvRect);
}

void Proyectil::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(sprite);
}
