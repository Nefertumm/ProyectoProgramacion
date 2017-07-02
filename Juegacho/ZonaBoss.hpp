#ifndef ZONA_HPP
#define ZONA_HPP

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Nuestro
#include "Game.hpp"
#include "Escena.hpp"
#include "Jugador.hpp"
#include "Plataforma.hpp"


class ZonaBoss : public Escena 
{
protected:
	sf::Music _ambiente;
	sf::Text _textPuntaje;
	sf::Font _fuentePuntaje;
	Jugador _jugador;
	float score;
	std::vector<Plataforma> m_plataformas;
	Plataforma p;
	
public:
	ZonaBoss(Game* game, sf::RenderWindow* wnd);
	~ZonaBoss();
	
	void Reiniciar();
	
	void Dibujar();
	void Actualizar(float dt);
	void ProcesarColisiones();
	void ProcesarEventos();
	
	void GameOver(int score);
	void nuevasPlataformas();
};

#endif

