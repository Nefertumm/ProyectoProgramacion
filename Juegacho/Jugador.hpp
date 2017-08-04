#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>
#include "Animaciones.hpp"

class Jugador
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture hitBoxText;
	sf::Sprite hitBox;
	
	// Constantes:
	const float velGravedad = 1800.f;
	const float dSalto = 110.f;
	const float movementSpeed = 300.f;
	
	bool isJumping;
	sf::Vector2f velocidad;
	bool canDoubleJump;
	bool keyReleased;
	
	// Extras:
	bool god, canBeAGod; sf::Clock godCd, godTime; sf::Texture textGod, textGodCd; sf::Sprite godSp;
	
	// Animaciones
	Animaciones* anim;
	bool mIzquierda;
	unsigned int fila;
	
	
public:
	Jugador();
	~Jugador();
	
	void Dibujar(sf::RenderWindow* wnd);
	void Actualizar(float dt);
	void mantenerJugadorEnPantalla();
	void setVelocity(sf::Vector2f vel) { velocidad = vel; }
	void move(sf::Vector2f v) { sprite.move(v); }
	void setJumping(bool jump) { isJumping = jump; canDoubleJump = true;}
	bool isGod() { return god; }
	
	sf::Vector2f getVelocidad() { return velocidad; }
	bool estaSaltando() { return isJumping; }
	sf::Sprite getSprite() { return hitBox; }
	void keyRel(bool keyReleased) { this->keyReleased = keyReleased; }
};

#endif

