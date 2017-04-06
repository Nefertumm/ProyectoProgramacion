#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include <SFML/Graphics.hpp>


class Jugador {
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	float _velocidad;
	sf::Vector2f _direccion;
	
	//Variables de gravedad:
	float _velGravedad;
	int _suelo;
	bool _isJumping;
	
public:
	Jugador();
	~Jugador();
	
	void Dibujar(sf::RenderWindow* wnd);
	void Actualizar(float dt);
	sf::FloatRect Bounds();
	
	void Saltar();
	void Derecha();
	void Izquierda();
	
	inline void estaSaltando(bool jumping) { _isJumping = jumping; }
	
};

#endif

