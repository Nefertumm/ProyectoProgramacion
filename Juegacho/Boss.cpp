#include "Boss.hpp"
#include <iostream>

Boss::Boss() : phase(PHASE_NONE), movementSpeed(250.f), down(false)
{
	if (!texture.loadFromFile("resources/boss.png"))
		std::cerr << "No se encontró la textura del boss." << std::endl;
	
	sprite.setTexture(texture);
	sprite.setScale(1.5f, 1.5f);
	sprite.setOrigin({ 59.f * 0.5f, 73.f * 0.5f });
	sprite.setPosition(sf::Vector2f(923.f - (sprite.getTextureRect().width/2.f * sprite.getScale().x), 600.f - (sprite.getTextureRect().height * sprite.getScale().y + 13.f)));
	
	velocidad = 0.f;
	difVel = 0.f;
	angle = 0.f;
	anim = new Animaciones(&texture, sf::Vector2u(5, 1), 0.2f);
	phaseTimer.restart();
}

Boss::~Boss()
{ 
	delete anim;
}

void Boss::Dibujar(sf::RenderWindow* wnd)
{
	wnd->draw(sprite);
}

void Boss::Actualizar(float dt)
{
	if (phaseTimer.getElapsedTime().asSeconds() > 10 && phase == PHASE_NONE)
		phase = PHASE_ONE;
	else if (phaseTimer.getElapsedTime().asSeconds() > 30 && phase == PHASE_ONE)
		phase = PHASE_TWO;
	
	switch(phase)
	{
		case PHASE_NONE:
			if (down)
				velocidad = movementSpeed;
			else
			{
				down = false;
				velocidad = -movementSpeed;
			}
			if (sprite.getPosition().y < 0)
			{
				down = true;
				velocidad = movementSpeed;
			}
			sprite.move(0.f, velocidad * dt);
			break;
		case PHASE_ONE:
			velocidad = 0.f;
			angle -=1.5f;
			sprite.setPosition(sf::Vector2f(800.f - (sprite.getTextureRect().width/2.f * sprite.getScale().x) - 100.f, 600.f/2.f));
			sprite.setRotation(angle);
			break;
		case PHASE_TWO:
			sprite.setRotation(0);
			if (difVel > 250.f)
				difVel += 1.f;
			if (down)
				velocidad = movementSpeed + difVel;
			else
			{
				down = false;
				velocidad = -movementSpeed - difVel;
			}
			if (sprite.getPosition().y < 0)
			{
				down = true;
				velocidad = movementSpeed + difVel;
			}
			sprite.move(0.f, velocidad * dt);
			break;
	}
	
	anim->Actualizar(0, dt, true);
	sprite.setTextureRect(anim->uvRect);
}
