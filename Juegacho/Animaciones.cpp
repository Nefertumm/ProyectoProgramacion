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

void Animaciones::Actualizar(int fila, float dt, bool mIzquierda)
{
	imgActual.y = fila;
	totalTime += dt;
	
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		imgActual.x++;
		
		if (imgActual.x >= cantImg.x || imgActual.x < 0)
			imgActual.x = 0;
		
		uvRect.top = imgActual.y * uvRect.height;
		
		if (mIzquierda)
		{
			uvRect.left = imgActual.x * abs(uvRect.width);
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			uvRect.left = (imgActual.x + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width);
		}
	}
}
