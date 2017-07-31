#ifndef ANIMACIONES_HPP
#define ANIMACIONES_HPP
#include <SFML/Graphics.hpp>

class Animaciones 
{
public:
	sf::IntRect uvRect;
	Animaciones(sf::Texture* textura, sf::Vector2u cantImg, float switchTime);
	~Animaciones();
	void Actualizar(int fila, float dt, bool mIzquierda = true);
	
protected:
	sf::Vector2u cantImg;
	sf::Vector2u imgActual;
	
	float totalTime;
	float switchTime;
};

#endif

