#include "ZonaBoss.hpp"
#include "EscenaGameOver.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd)
{
	if (!_ambiente.openFromFile("resources/boss.ogg"))
		std::cerr << "No se pudo cargar la musica del boss." << std::endl;
	if (!_fuentePuntaje.loadFromFile("resources/arial.ttf"))
		std::cerr << "No se pudo cargar el archivo fuente" << std::endl;
	score = 0;
	
	_ambiente.setVolume(0); // cambiar a 100 cuando ya este hecho.
	_ambiente.setLoop(true);
	_ambiente.play();
	
	_textPuntaje.setFont(_fuentePuntaje);
	_textPuntaje.setColor(Color::Black);
	
	nuevasPlataformas();
}

ZonaBoss::~ZonaBoss() { }

bool sat_test(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *out_mtv = nullptr){ // Algoritmo de Pablo Abratte
	const sf::FloatRect &rectSp1 = sp1.getGlobalBounds();
	const sf::FloatRect &rectSp2 = sp2.getGlobalBounds();
	float proj_x, proj_y, overlap_x, overlap_y;
	
	// test overlap in x axis
	proj_x = std::max(rectSp1.left+rectSp1.width, rectSp2.left+rectSp2.width)-std::min(rectSp1.left, rectSp2.left);
	if(proj_x < rectSp1.width+ rectSp2.width){
		if(out_mtv){
			// calculate mtv in x
			overlap_x = rectSp1.width+ rectSp2.width - proj_x;
		}
		// test overlap in y axis
		proj_y = std::max(rectSp1.top+rectSp1.height, rectSp2.top+rectSp2.height)-std::min(rectSp1.top, rectSp2.top);
		if(proj_y < rectSp1.height+ rectSp2.height){
			if(out_mtv){
				// calculate mtv in y
				overlap_y = rectSp1.height+ rectSp2.height - proj_y;
				out_mtv->x = out_mtv->y = 0;
				
				// choose minimun overlap
				if(overlap_x < overlap_y){
					out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left?-1:1);
				}else{
					out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top?-1:1);
				}
			}
			return true;
		}
	}
	return false;
}


void ZonaBoss::Dibujar() 
{
	_wnd->clear(sf::Color::White);
	_wnd->draw(_textPuntaje);
	_jugador.Dibujar(_wnd);
	for(Plataforma plat : m_plataformas)
	{
		Plataforma p;
		p = plat;
		p.Dibujar(_wnd);
	}
	_wnd->display();
}

void ZonaBoss::ProcesarColisiones()
{
	
}

void ZonaBoss::ProcesarEventos()
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		switch (e.type)
		{
			case sf::Event::Closed:
				_wnd->close();
				break;
			default:
				break;
		}
	}
}

void ZonaBoss::Reiniciar() { }

void ZonaBoss::GameOver(int score)
{
	_game->CambiarEscena(new EscenaGameOver(_game, _wnd, score));
}

void ZonaBoss::Actualizar(float dt)
{
	score += dt;
	std::stringstream sc;
	sc << "Score: " << int(score);
	_textPuntaje.setString(sc.str());
	
	_jugador.Actualizar(dt);
	
	if (sf::Keyboard::isKeyPressed(Keyboard::L))
		GameOver(score);
}

void ZonaBoss::nuevasPlataformas()
{
	for(int i=0;i<4;i++) 
	{
		Plataforma plat;
		std::srand(std::time(0));
		plat.setPosition(sf::Vector2f(rand()%800, rand()%600));
		m_plataformas.push_back(plat);
	}
}
