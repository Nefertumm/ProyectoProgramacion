#include "ZonaBoss.hpp"
#include "EscenaGameOver.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>


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

ZonaBoss::ZonaBoss(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd), freezed(false), canFreeze(false) 
{
	if (!ambiente.openFromFile("resources/boss.ogg"))
		std::cerr << "No se pudo cargar la musica del boss." << std::endl;
	if (!fuentePuntaje.loadFromFile("resources/arial.ttf"))
		std::cerr << "No se pudo cargar el archivo fuente" << std::endl;
	if (!textSuelo.loadFromFile("resources/suelo.png"))
		std::cerr << "No se pudo cargar la textura del suelo" << std::endl;
	if (!textFondo.loadFromFile("resources/fondo.jpg"))
		std::cerr << "No se pudo cargar la textura del fondo" << std::endl;
	if (!textFreeze.loadFromFile("resources/freeze.png"))
		std::cerr << "No se pudo cargar la textura del freeze" << std::endl;
	if (!textFreezeCd.loadFromFile("resources/freezeCd.png"))
		std::cerr << "No se pudo cargar la textura del freeze" << std::endl;
	score = 0;

	fondo.setTexture(textFondo);
	freezeSp.setPosition({ 0.f, 40.f });
	freezeSp.setTexture(textFreezeCd);
	ambiente.setVolume(70); 
	ambiente.setLoop(true);
	ambiente.play();
	
	textPuntaje.setFont(fuentePuntaje);
	textPuntaje.setFillColor(Color::Black);
	srand(time(nullptr));
	
	suelo.setTexture(textSuelo);
	suelo.setPosition(0.0f, 587.f);
	timer.restart();
	timerPlat.restart();
	freezeTimer.restart();
	freezeCdTimer.restart();
	
	npcs.push_back(new NpcBoss);
	
	difProyPhaseNone = 1.75f;
	difProyPhaseTwo = 1.f;
	nuevasPlataformas();
}

ZonaBoss::~ZonaBoss() { }
void ZonaBoss::Dibujar() 
{
	_wnd->clear(sf::Color::White);
	_wnd->draw(fondo);
	_wnd->draw(textPuntaje);
	_wnd->draw(suelo);
	_wnd->draw(freezeSp);
	jugador.Dibujar(_wnd);
	boss.Dibujar(_wnd);
	for(auto &itr_proy : proy)
		itr_proy->Dibujar(_wnd);
	for(auto &itr_plat : m_plat) 
		itr_plat->Dibujar(_wnd);
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
			case sf::Event::KeyReleased:
				if (e.key.code == sf::Keyboard::Up)
				{
					jugador.keyRel(true);
					for(auto &itr_npc : npcs)
						itr_npc->keyRel(true);
				}
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
		if(sat_test(jugador.getSprite(), m_plat[i]->getSprite(), &vec)){
			jugador.move(vec);
			if(vec.x != 0)
				jugador.setVelocity({0, jugador.getVelocidad().y});
			if(vec.y !=0)
			{
				jugador.setVelocity({jugador.getVelocidad().x, 0});
				if (vec.y <= 0)
					jugador.setJumping(false);
			}
		}
	}
	
	if (sat_test(jugador.getSprite(), boss.getSprite()) && !jugador.isGod())
		GameOver(score);
	
	if (sat_test(jugador.getSprite(), suelo, &vec))
	{
		jugador.move(vec);
		if(vec.y !=0)
		{
			jugador.setVelocity({jugador.getVelocidad().x, 0});
			jugador.setJumping(false);
		}
	}
	
	for (auto &itr_npc : npcs)
	{
		if (sat_test(itr_npc->getSprite(), suelo, &vec))
		{
			itr_npc->move(vec);
			if(vec.y !=0)
			{
				itr_npc->setVelocity({itr_npc->getVelocidad().x, 0});
				itr_npc->setJumping(false);
			}
		}
		if (sat_test(jugador.getSprite(), itr_npc->getSprite()) && !jugador.isGod())
			GameOver(score);
		
		for(int i=0;i<cant_plat;i++) 
		{
			if(sat_test(itr_npc->getSprite(), m_plat[i]->getSprite(), &vec)){
				itr_npc->move(vec);
				if(vec.y !=0)
				{
					itr_npc->setVelocity({itr_npc->getVelocidad().x, 0});
					if (vec.y <= 0)
						itr_npc->setJumping(false);
				}
			}
		}
	}
	
	if (sat_test(boss.getSprite(), suelo, &vec))
	{
		npcs.push_back(new NpcBoss);
		boss.setDown(false);
	}
	
	for(int i=0;i<cant_plat;i++) 
	{
		for(auto &itr_proy : proy)
		{
			if (sat_test(m_plat[i]->getSprite(), itr_proy->getSprite(), &vec))
			{
				if (vec.y != 0)
					if (vec.y*itr_proy->getVelocidad().y>0)
						itr_proy->setVelocity({ itr_proy->getVelocidad().x, -itr_proy->getVelocidad().y });
				if (vec.x != 0)
					if (vec.x*itr_proy->getVelocidad().x>0)
						itr_proy->setVelocity({ -itr_proy->getVelocidad().x, itr_proy->getVelocidad().y });
					
			}
		}
	}
	
	for(auto &itr_proy : proy)
	{
		if (sat_test(itr_proy->getSprite(), suelo, &vec))
			if (vec.y != 0)
				itr_proy->setVelocity({itr_proy->getVelocidad().x, -itr_proy->getVelocidad().y});
		
		if(itr_proy->getPosition().y < 0.f)
		{
			itr_proy->setPosition({itr_proy->getPosition().x,0.f});
			itr_proy->setVelocity({itr_proy->getVelocidad().x, -itr_proy->getVelocidad().y});
		}
		if (sat_test(jugador.getSprite(), itr_proy->getSprite()) && !jugador.isGod())
			GameOver(score);
	}
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
	textPuntaje.setString(sc.str());
	
	// ******* Mecanica de congelar tiempo -- Inicio *******
	if (freezeCdTimer.getElapsedTime().asSeconds() > 10 && canFreeze == false)
	{
		freezeDif = 3;
		canFreeze = true;
		freezeSp.setTexture(textFreeze);
	}
	if (freezeTimer.getElapsedTime().asSeconds() > 3 && freezed == true)
		freezed = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && canFreeze)
	{
		freezeTimer.restart();
		freezed = true;
		freezeCdTimer.restart();
		canFreeze = false;
		freezeSp.setTexture(textFreezeCd);
	}
	if (freezed)
		if (freezeDif > 1)
		{
			freezeDif -= 0.01f;
			dt /= freezeDif;
		}
	
	// ******* Mecanica de congelar tiempo -- Fin *******
	
	jugador.Actualizar(dt);
	boss.Actualizar(dt);
	
	auto npcs_end = std::remove_if(npcs.begin(), npcs.end(), NpcBoss::outOfScreen);
	npcs.erase(npcs_end, npcs.end()); // el remove_if no hace un resize del vector.
	auto proy_end = std::remove_if(proy.begin(), proy.end(), Proyectil::outOfScreen);
	proy.erase(proy_end, proy.end());
	
	
	sf::Vector2f velocidadProyectil(0.f, 0.f);
	if (timer.getElapsedTime().asSeconds() > difProyPhaseNone && boss.getPhase() == PHASE_NONE)
	{
		difProyPhaseNone -= 0.15f;
		proy.push_back(new Proyectil);
		int r = proy.size()-1;
		proy[r]->setPosition(sf::Vector2f(boss.getPosition().x, boss.getPosition().y + boss.getSprite().getTextureRect().height/2.0f));
		direccionarVector(jugador.getSprite(), boss.getSprite(), &velocidadProyectil, 500.f);
		proy[r]->setVelocity(velocidadProyectil);
		timer.restart();
	}
	else if (timer.getElapsedTime().asSeconds() > 0.1f && boss.getPhase() == PHASE_ONE)
	{
		proy.push_back(new Proyectil);
		int r = proy.size()-1;
		proy[r]->setPosition(sf::Vector2f(boss.getPosition().x, boss.getPosition().y + boss.getSprite().getTextureRect().height/2.0f));
		direccionarVector(boss.getSprite(), &velocidadProyectil, 500.f);
		proy[r]->setVelocity(velocidadProyectil);
		timer.restart();
	}
	else if (timer.getElapsedTime().asSeconds() > difProyPhaseTwo && boss.getPhase() == PHASE_TWO)
	{
		if (difProyPhaseTwo > 0.5f)
			difProyPhaseTwo -= 0.01f;
		int angle = 135;
		for(int i=0;i<8;i++) 
		{
			proy.push_back(new Proyectil);
			int r = proy.size()-1;
			proy[r]->setPosition(sf::Vector2f(boss.getPosition().x, boss.getPosition().y + boss.getSprite().getTextureRect().height/2.0f));
			direccionarVector(angle, &velocidadProyectil, 250.f);
			proy[r]->setVelocity(velocidadProyectil);
			angle += 11.25f;
		}
		timer.restart();
	}
	
	for(auto &itr_proy : proy)
		itr_proy->Actualizar(dt);
	
	for(auto &itr_npc : npcs)
		itr_npc->Actualizar(dt);
	
	if (timerPlat.getElapsedTime().asSeconds() > 10)
	{
		timerPlat.restart();
		nuevasPlataformas();
	}
}

void ZonaBoss::nuevasPlataformas()
{
	m_plat.clear();
	for(int i=0;i<cant_plat;i++)
	{
		m_plat.push_back(new Plataforma);
		sf::Vector2f vec(0.f, 0.f);
		switch (i)
		{ 
			case 0:
				vec = { float(80+rand()%(130+1)), float(100+rand()%(150+1)) };
				if (vec.y >= 200)
					vec.y = 150.f;
				m_plat[i]->setPosition(vec);
				break;
			case 1:
				vec = { float(300+rand()%(450+1)), float(100+rand()%(150+1)) };
				if (vec.x >= 500)
					vec.x = 400.f;
				if (vec.y >= 200)
					vec.y =150.f;
				m_plat[i]->setPosition(vec);
				break;
			case 2:
				vec = { float(80+rand()%(130+1)), float(150+rand()%(180+1)) };
				if (vec.y <= 250)
					vec.y = 350.f;
				m_plat[i]->setPosition(vec);
				break;
			case 3:
				vec = { float(300+rand()%(450+1)), float(150+rand()%(180+1)) };
				if (vec.y <= 250)
					vec.y = 350.f;
				if (vec.x >= 500)
					vec.x = 400.f;
				m_plat[i]->setPosition(vec);
				break;
			case 4:
				vec = { float(80+rand()%(130+1)), float(250+rand()%(280+1)) };
				if (vec.y <= 400)
					vec.y = 450.f;
				if (vec.y >= 500)
					vec.y = 450.f;
				m_plat[i]->setPosition(vec);
				break;
			case 5:
				vec = { float(300+rand()%(450+1)), float(250+rand()%(280+1)) };
				if (vec.x >= 500)
					vec.x = 400.f;
				if (vec.y <= 400)
					vec.y = 450.f;
				if (vec.y >= 500)
					vec.y = 450.f;
				m_plat[i]->setPosition(vec);
				break;
		}
	}              
}



void ZonaBoss::direccionarVector(const sf::Sprite &sp1, const sf::Sprite &sp2, sf::Vector2f *diff, float vel)
{
	float dx = (sp1.getPosition().x - sp2.getPosition().x);
	float dy = (sp1.getPosition().y - sp2.getPosition().y);
	float unitario = float(sqrt(pow(dx, 2) + pow(dy, 2)));
	diff->x = (dx / unitario) * vel;
	diff->y = (dy / unitario) * vel;
}

void ZonaBoss::direccionarVector(const sf::Sprite &sp, sf::Vector2f *diff, float vel)
{
	float cosx = -cos(sp.getRotation() * G2R);
	float seny = -sin(sp.getRotation() * G2R);
	float unitario = sqrt(pow(cosx, 2) + pow(seny, 2));
	diff->x = (cosx / unitario) * vel;
	diff->y = (seny / unitario) * vel;
}

void ZonaBoss::direccionarVector(float angle, sf::Vector2f *diff, float vel)
{
	float cosx = cos(angle * G2R);
	float seny = sin(angle * G2R);
	diff->x = cosx * vel;
	diff->y = seny * vel;
}
