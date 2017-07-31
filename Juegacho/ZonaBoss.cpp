#include "ZonaBoss.hpp"
#include "EscenaGameOver.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>


ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd)
{
//	if (!_ambiente.openFromFile("resources/boss.ogg"))
//		std::cerr << "No se pudo cargar la musica del boss." << std::endl;
	if (!_fuentePuntaje.loadFromFile("resources/arial.ttf"))
		std::cerr << "No se pudo cargar el archivo fuente" << std::endl;
	if (!textSuelo.loadFromFile("resources/platform.png"))
		std::cerr << "No se pudo cargar el sprite del suelo" << std::endl;
	score = 0;

//	_ambiente.setVolume(0); // cambiar a 100 cuando ya este hecho.
//	_ambiente.setLoop(true);
//	_ambiente.play();
	
	_textPuntaje.setFont(_fuentePuntaje);
	_textPuntaje.setColor(Color::Black);
	srand(time(nullptr));
	
	suelo.setTexture(textSuelo);
	suelo.setScale(6.25f, 0.1f);
	suelo.setPosition(0.0f, 587.f);
	
	nuevasPlataformas();
	for(int i=0;i<cant_plat;i++) 
		std::cout << i << " " << m_plat[i].getPosition().y << std::endl;
	
	
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
	_wnd->draw(suelo);
	_jugador.Dibujar(_wnd);
	for(int i=0;i<cant_plat;i++) 
		m_plat[i].Dibujar(_wnd);
	for (auto &itr_npc : npcs)
		itr_npc->Dibujar(_wnd);
	_wnd->display();
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

void ZonaBoss::ProcesarColisiones() 
{
	sf::Vector2f vec(0.f, 0.f);
	for(int i=0;i<cant_plat;i++) 
	{
		if(sat_test(_jugador.getSprite(), m_plat[i].getSprite(), &vec)){
			_jugador.move(vec);
			if(vec.x != 0)
				_jugador.setVelocity({0, _jugador.getVelocidad().y});
			if(vec.y !=0)
			{
				_jugador.setVelocity({_jugador.getVelocidad().x, 0});
				if (vec.y <= 0)
				{
					_jugador.setJumping(false);
					std::cout << "Se toca en y" << vec.y << std::endl;
				}
			}
		}
	}
	
	if (sat_test(_jugador.getSprite(), suelo, &vec))
	{
		_jugador.move(vec);
		if(vec.y !=0)
		{
			_jugador.setVelocity({_jugador.getVelocidad().x, 0});
			_jugador.setJumping(false);
		}
	}
	
	for (auto itr_npc : npcs)
		if (sat_test(itr_npc->getSprite(), suelo, &vec))
		{
			itr_npc->move(vec);
			if(vec.y !=0)
			{
				itr_npc->setVelocity({itr_npc->getVelocidad().x, 0});
				itr_npc->setJumping(false);
			}
		}
	
//	if (sat_test(_jugador.getSprite(), npc.getSprite()))
//		GameOver(score);
}


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
	
	for(auto itr_npc : npcs)
		itr_npc->Actualizar(dt);
	
	if (sf::Keyboard::isKeyPressed(Keyboard::L))
		GameOver(score);
}

void ZonaBoss::nuevasPlataformas()
{
	std::vector<Plataforma> v_plat;
	for(int i=0;i<cant_plat;i++)
	{
		if (i<=2)
			m_plat[i].setPosition(sf::Vector2f(rand()%300+100*i, rand()%200+400-130*0.4));
		else if (i > 2 && i <= 4)
			m_plat[i].setPosition(sf::Vector2f(rand()%300+50*i, rand()%200+200-130*0.4));
		else 
			m_plat[i].setPosition(sf::Vector2f(rand()%300+10*i, rand()%200-130*0.4));
		
		v_plat.push_back(m_plat[i]);
	}
	
	sort(v_plat.begin(), v_plat.end());
	reverse(v_plat.begin(), v_plat.end());
	for(int i=0;i<v_plat.size();i++) 
		m_plat[i] = v_plat[i];
	
	for(int i=0;i<cant_plat;i++) 
	{ 
		if (i+1 <= cant_plat)
		{
			sf::Vector2f pos1 = m_plat[i].getPosition(), pos2 = m_plat[i+1].getPosition(), deltaPos;
			deltaPos.y = pos1.y - pos2.y;
			if ((deltaPos.y > 0) && (deltaPos.y+128*0.1) < 49)
			{
				pos2.y -= 49;
				m_plat[i+1].setPosition(pos2);
			} 
			else if ((deltaPos.y < 0) && deltaPos.y > -49)
			{
				pos1.y -= 49;
				m_plat[i].setPosition(pos1);
			}
		}
	}
}
