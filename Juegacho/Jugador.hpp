#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>


class Jugador 
{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	const float _suelo = 550.f;
	
	//Variables de gravedad:
	float _velGravedad;
	bool _isJumping;
	float _dSalto;
	float _movementSpeed;
	sf::Vector2f _velocidad;
	
public:
	Jugador();
	~Jugador();
	
	void Dibujar(sf::RenderWindow* wnd);
	void Actualizar(float dt);
	sf::FloatRect Bounds();
	void mantenerJugadorEnPantalla();
	void setVelocity(sf::Vector2f vel);
	
	inline sf::Vector2f getVelocidad() { return _velocidad; } // Nos va a servir para más tarde..
	inline bool isJumping() { return _isJumping; }
	inline sf::Sprite getSprite() { return _sprite; }
};

#endif

