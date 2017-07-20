#include "Animaciones.hpp"

Animaciones::Animaciones(sf::Texture* textura, sf::Vector2u cantImg, float switchTime) 
{
	this->cantImg = cantImg;
	this->switchTime = switchTime;
	
	totalTime = 0.f;
	imgActual.x = 0;
	
	uvRect.width = textura->getSize().x / float(cantImg.x);
	uvRect.height = textura->getSize().y / float(cantImg.y);
}

Animaciones::~Animaciones() { }

void Animaciones::Actualizar(int fila, float dt)
{
	imgActual.y = fila;
	totalTime += dt;
	
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		imgActual.x++;
		
		if (imgActual.x >= cantImg.x)
			imgActual.x = 0;
		
		uvRect.left = imgActual.x * uvRect.width;
		uvRect.top = imgActual.y * uvRect.height;
	}
}
