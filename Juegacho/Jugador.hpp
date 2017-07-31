#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>
#include "Animaciones.hpp"

class Jugador
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	
	//Variables de gravedad:
	const float velGravedad = 1800.f;
	bool isJumping;
	const float dSalto = 150.f;
	const float movementSpeed = 300.f;
	sf::Vector2f velocidad;
	
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
	void setJumping(bool jump) { isJumping = jump; }
	
	sf::Vector2f getVelocidad() { return velocidad; }
	bool estaSaltando() { return isJumping; }
	sf::Sprite getSprite() { return sprite; }
};

#endif

