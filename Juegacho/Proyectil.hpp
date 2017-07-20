#ifndef PROYECTIL_HPP
#define PROYECTIL_HPP
#include <SFML/Graphics.hpp>
#include "Animaciones.hpp"

class Proyectil 
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	Animaciones* anim;
public:
	Proyectil();
	~Proyectil();
	
	void Actualizar(float dt);
	void Dibujar(sf::RenderWindow* wnd);
};

#endif

