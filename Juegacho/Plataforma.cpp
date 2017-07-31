#include "Plataforma.hpp"
#include <iostream>

Plataforma::Plataforma() 
{
	if (!m_texture.loadFromFile("resources/Blocks.png"))
		std::cerr << "No se pudo cargar el sprite de la plataforma." << std::endl;
	
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(1, 0.9);
}

Plataforma::~Plataforma() { }

void Plataforma::Actualizar(float dt) { }

void Plataforma::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(m_sprite);
}

void Plataforma::setPosition(sf::Vector2f posicion)
{
	m_sprite.setPosition(posicion);
}
