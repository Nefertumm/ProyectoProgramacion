#ifndef GAME_HPP
#define GAME_HPP

#include "Escena.hpp"
#include <SFML/Graphics.hpp>

struct Puntuacion
{
	std::string _nombre = "AAAAAAAA";
	int _puntos = 0;
};

class Escena;

class Game 
{
	public:
		Game();
		void run();
		~Game();
		
		void CambiarEscena(Escena* nuevaEscena);
	
	protected:		
		sf::RenderWindow* wnd;
		Escena* _escenaActual;
		Escena* _escenaAnterior;
		sf::Clock _clock;
		
};

#endif
