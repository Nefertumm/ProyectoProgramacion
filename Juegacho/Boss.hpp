#ifndef BOSS_HPP
#define BOSS_HPP
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "NpcBoss.hpp"

class Boss 
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	int time;
	vector<NpcBoss> npcs;

public:
	Boss();
	~Boss();
	
	void Dibujar(RenderWindow* wnd);
	void Actualizar(float dt);
};

#endif

