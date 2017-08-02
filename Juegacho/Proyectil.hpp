#ifndef PROYECTIL_HPP
#define PROYECTIL_HPP
#include <SFML/Graphics.hpp>
#include "Animaciones.hpp"

class Proyectil 
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Animaciones* anim;
	sf::Vector2f velocidad;
public:
	Proyectil();
	~Proyectil();
	
	void Actualizar(float dt);
	void Dibujar(sf::RenderWindow* wnd);
	void setVelocity(sf::Vector2f vec) { velocidad = vec; }
	sf::Vector2f getVelocidad() { return velocidad;}
	void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::Sprite getSprite() { return sprite; }
	void move(sf::Vector2f v) { sprite.move(v); };
	
	static bool outOfScreen(Proyectil* proy)
	{
		if (proy->getPosition().x < 0.f || proy->getPosition().x > 800.f || proy->getPosition().y < 0.f || proy->getPosition().y > 600.f)
			return true;
		
		return false;
	}
};

#endif

