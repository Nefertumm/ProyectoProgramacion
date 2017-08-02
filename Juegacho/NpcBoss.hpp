#ifndef NPCBOSS_HPP
#define NPCBOSS_HPP
#include <SFML/Graphics.hpp>
#include "Animaciones.hpp"

class NpcBoss
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Animaciones* anim;
	
	sf::Vector2f velocidad;
	bool isJumping;
	const float velGravedad = 1800.f;
	const float dSalto = 110.f;
	bool canDoubleJump;
	bool keyReleased;
	
public:
	NpcBoss();
	~NpcBoss();
	
	void Dibujar(sf::RenderWindow* wnd);
	void Actualizar(float dt);
	sf::Sprite getSprite() { return sprite; }
	void move(sf::Vector2f v) { sprite.move(v); }
	bool setJumping(bool jump) { isJumping = jump; canDoubleJump = true; }
	void setVelocity(sf::Vector2f vel) { velocidad = vel; }
	
	sf::Vector2f getVelocidad() { return velocidad; }
	bool estaSaltando() { return isJumping; }
	void keyRel(bool keyReleased) { this->keyReleased = keyReleased; }
};

#endif

