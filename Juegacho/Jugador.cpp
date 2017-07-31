#include "Jugador.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Jugador::Jugador() : isJumping(false)
{	
	if (!texture.loadFromFile("resources/jugador.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	
	sprite.setTexture(texture);
	
	sprite.setPosition(0.0f, 550.f);
	
	mIzquierda = false;
	anim = new Animaciones(&texture, sf::Vector2u(8, 3), 0.1f);

	velocidad = { 0.f, 0.f };
}

Jugador::~Jugador() 
{
	delete anim;
}

void Jugador::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(sprite);
}

void Jugador::Actualizar(float dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocidad.x = -movementSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocidad.x = movementSpeed;
	else
		velocidad.x = 0;
	
	if (velocidad.x == 0)
		fila = 0;
	else
	{
		fila = 1;
		
		if (velocidad.x < 0.0f)
			mIzquierda = true;
		else
			mIzquierda = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
	{
		isJumping = true;
		velocidad.y = (float)-sqrtf(2.0f * velGravedad * dSalto);
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y-1);
	}
	

	if(isJumping)
	{
		velocidad.y += dt * velGravedad;
	}
	
	anim->Actualizar(fila, dt, mIzquierda);
	sprite.setTextureRect(anim->uvRect);
	sprite.move(velocidad * dt);
	
	mantenerJugadorEnPantalla();
}

void Jugador::mantenerJugadorEnPantalla() 
{
	if (sprite.getPosition().x <= 0.f)
		sprite.setPosition( sf::Vector2f(0.f, sprite.getPosition().y) );
	else if (sprite.getPosition().x > (740 - sprite.getTextureRect().width/2))
		sprite.setPosition( sf::Vector2f(740 - sprite.getTextureRect().width/2, sprite.getPosition().y) );
}
