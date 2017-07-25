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
#include "Boss.hpp"
#include "Proyectil.hpp"

#define cant_plat 6

class ZonaBoss : public Escena 
{
protected:
	sf::Music _ambiente;
	sf::Text _textPuntaje;
	sf::Font _fuentePuntaje;
	Jugador _jugador;
	float score;
	Plataforma m_plat[cant_plat];
	
public:
	ZonaBoss(Game* game, sf::RenderWindow* wnd);
	~ZonaBoss();
	
	void Reiniciar();
	
	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override;
	void ProcesarEventos() override;
	
	void GameOver(int score);
	void nuevasPlataformas();
};

#endif

