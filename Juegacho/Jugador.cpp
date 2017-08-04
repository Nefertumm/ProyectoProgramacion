#include "Jugador.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Jugador::Jugador() : isJumping(false), canDoubleJump(true), keyReleased(true), god(false), canBeAGod(true)
{	
	if (!texture.loadFromFile("resources/jugador.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	if (!hitBoxText.loadFromFile("resources/hitBox.png"))
		std::cerr << "No se pudo encontrar la textura" << std::endl;
	if (!textGod.loadFromFile("resources/god.png"))
		std::cerr << "No se pudo encontrar la textura de god" << std::endl;
	if (!textGodCd.loadFromFile("resources/godCd.png"))
		std::cerr << "No se pudo encontrar la textura de godCd" << std::endl;
	
	sprite.setTexture(texture);
	
	sprite.setPosition(0.0f, 550.f);
	godSp.setPosition(35.f, 40.f);
	godSp.setTexture(textGod);
	
	hitBox.setTexture(hitBoxText);
	hitBox.setPosition(sf::Vector2f(sprite.getPosition().x + 15.f, sprite.getPosition().y));
	
	mIzquierda = false;
	anim = new Animaciones(&texture, sf::Vector2u(8, 3), 0.1f);
	
	godCd.restart();
	godTime.restart();

	velocidad = { 0.f, 0.f };
}

Jugador::~Jugador() 
{
	delete anim;
}

void Jugador::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(sprite);
	wnd->draw(hitBox);
	wnd->draw(godSp);
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

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keyReleased) && (!isJumping || canDoubleJump))
	{
		keyReleased = false;
		if (isJumping)
			canDoubleJump = false;
		isJumping = true;
		velocidad.y = (float)-sqrtf(2.0f * velGravedad * dSalto);
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y-1);
	}
	
	// ******** Mecanica de Dios -- Inicio. ********
	if (godCd.getElapsedTime().asSeconds() > 6 && canBeAGod == false)
	{
		canBeAGod = true;
		godSp.setTexture(textGod);
	}
	if (godTime.getElapsedTime().asSeconds() > 2 && god == true)
		god = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && canBeAGod)
	{
		godTime.restart();
		god = true;
		canBeAGod = false;
		godCd.restart();
		godSp.setTexture(textGodCd);
	}
	// ******* Mecanica de Dios -- Final. ********
	
	velocidad.y += dt * velGravedad;
	
	anim->Actualizar(fila, dt, mIzquierda);
	sprite.setTextureRect(anim->uvRect);
	sprite.move(velocidad * dt);
	
	hitBox.setPosition(sf::Vector2f(sprite.getPosition().x + 15.f, sprite.getPosition().y));
	
	mantenerJugadorEnPantalla();
}

void Jugador::mantenerJugadorEnPantalla() 
{
	if (sprite.getPosition().x <= 0.f)
		sprite.setPosition( sf::Vector2f(0.f, sprite.getPosition().y) );
	else if (sprite.getPosition().x > (740 - sprite.getTextureRect().width/2))
		sprite.setPosition( sf::Vector2f(740 - sprite.getTextureRect().width/2, sprite.getPosition().y) );
	
	if (sprite.getPosition().y < 0.f)
	{
		velocidad.y = 0;
		sprite.setPosition( sf::Vector2f(sprite.getPosition().x, 0.0f) );
	}
}
