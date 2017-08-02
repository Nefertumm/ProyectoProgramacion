#ifndef BOSS_HPP
#define BOSS_HPP
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Animaciones.hpp"


enum Phases
{
	PHASE_NONE = 0,
	PHASE_ONE = 1,
	PHASE_TWO = 2
};

class Boss 
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Animaciones* anim;
	float movementSpeed;
	float velocidad;
	bool down;
	sf::Clock phaseTimer;
	float angle;
	float difVel;
	
	int8_t phase;

public:
	Boss();
	~Boss();
	
	void Dibujar(RenderWindow* wnd);
	void Actualizar(float dt);
	sf::Sprite getSprite() { return sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	void setDown(bool d) { down = d; }
	
	int8_t getPhase() { return phase; }
	void setPhase(int8_t p) { phase = p; }
};

#endif

