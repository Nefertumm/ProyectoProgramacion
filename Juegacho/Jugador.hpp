#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>


class Jugador {
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	sf::Vector2f _velocidad;
	
	//Variables de gravedad:
	float _velGravedad;
	int _suelo;
	bool _isJumping;
	float _dSalto;
	float _movementSpeed;
	
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

