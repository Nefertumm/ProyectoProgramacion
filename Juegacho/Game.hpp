#ifndef GAME_HPP
#define GAME_HPP

#include "Escena.hpp"
#include <SFML/Graphics.hpp>
#include "ManejoPuntuacion.hpp"

class Escena;

class Game 
{
	public:
		Game();
		void run();
		~Game();
		
		ManejoPuntuacion manPun;
		
		void CambiarEscena(Escena* nuevaEscena);
	
	protected:		
		sf::RenderWindow* wnd;
		Escena* _escenaActual;
		Escena* _escenaAnterior;
		sf::Clock _clock;
		
};

#endif
