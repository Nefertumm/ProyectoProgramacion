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
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }
	
};

inline bool operator<(Plataforma &p1, Plataforma &p2)
{
	sf::Vector2f pos1 = p1.getPosition(), pos2 = p2.getPosition();
	return pos1.y < pos2.y;
}

#endif

