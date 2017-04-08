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
	
	inline void estaSaltando(bool jumping) { _isJumping = jumping; }
	inline bool isJumping() { return _isJumping; }
	
};

#endif

