#include "NpcBoss.hpp"
#include <iostream>

NpcBoss::NpcBoss() : isJumping(false), canDoubleJump(true), keyReleased(true)
{
	if (!texture.loadFromFile("resources/NpcBoss.png"))
		std::cerr << "No se encontro la textura del NpcBoss" << std::endl;
	
	sprite.setTexture(texture);
	anim = new Animaciones(&texture, sf::Vector2u(7, 1), 0.15f);
	velocidad = { -250.f, 0.f };
	
	sprite.setPosition(800.f, 550.f);
}

NpcBoss::~NpcBoss()
{
	delete anim;
}

void NpcBoss::Dibujar(sf::RenderWindow* wnd) 
{
	wnd->draw(sprite);
}

void NpcBoss::Actualizar(float dt)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keyReleased) && (!isJumping || canDoubleJump))
	{
		keyReleased = false;
		if (isJumping)
			canDoubleJump = false;
		isJumping = true;
		velocidad.y = (float)-sqrtf(2.0f * velGravedad * dSalto);
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y-1);
	}
	
	velocidad.y += dt * velGravedad;
	
	anim->Actualizar(0, dt);
	sprite.setTextureRect(anim->uvRect);
	sprite.move(velocidad * dt);
}
