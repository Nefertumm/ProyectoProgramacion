#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP
#include "SFML/Graphics.hpp"

class Plataforma 
{
protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
public:
	Plataforma();
	~Plataforma();
	
	sf::Sprite getSprite() { return m_sprite; }
	void Dibujar(sf::RenderWindow* wnd);
	void Actualizar(float dt);
	void setPosition(sf::Vector2f posicion);
	
};

#endif

