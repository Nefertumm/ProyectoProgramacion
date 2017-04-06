#ifndef GAME_HPP
#define GAME_HPP

#include "Escena.hpp"
#include <SFML/Graphics.hpp>


class Escena;

class Game {
	public:
		Game();
		void run();
		~Game();
		
		void CambiarEscena(Escena* nuevaEscena);
	
	protected:		
		sf::RenderWindow* wnd;
		Escena* _escenaActual;
		sf::Clock _clock;
		
};

#endif
