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
#include "NpcBoss.hpp"

#define cant_plat 6
const double G2R = 3.1415/180;

class ZonaBoss : public Escena 
{
protected:
	sf::Music ambiente;
	sf::Text textPuntaje;
	sf::Font fuentePuntaje;
	sf::Texture textSuelo; sf::Sprite suelo; // suelo
	sf::Texture textFondo; sf::Sprite fondo;
	Jugador jugador;
	float score;
	std::vector<Plataforma*> m_plat;
	std::vector<NpcBoss*> npcs;
	Boss boss;
	std::vector<Proyectil*> proy;
	sf::Clock timer, timerPlat, freezeTimer, freezeCdTimer;
	float difProyPhaseNone, difProyPhaseTwo;
	bool freezed, canFreeze; sf::Texture textFreeze, textFreezeCd; sf::Sprite freezeSp;
	float freezeDif;
	
public:
	ZonaBoss(Game* game, sf::RenderWindow* wnd);
	~ZonaBoss();
	
	void Dibujar() override;
	void Actualizar(float dt) override;
	void ProcesarColisiones() override;
	void ProcesarEventos() override;
	
	void GameOver(int score);
	void nuevasPlataformas();
	
	void direccionarVector(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *diff, float vel);
	void direccionarVector(const sf::Sprite &sp, sf::Vector2f *diff, float vel);
	void direccionarVector(float angle, sf::Vector2f *diff, float vel);
};

#endif

