#include "Controles.hpp"
#include "Menu.hpp"

Controles::Controles(Game* game, sf::RenderWindow* wnd) : Escena(game, wnd)
{
	if(!fuente.loadFromFile("resources/Equestria.otf")) 
		std::cerr << "No se encontro la fuente del menu" << std::endl;
	
	controles.setFont(fuente);
	controles.setString("Controles");
	controles.setCharacterSize(62);
	controles.setFillColor(Color::White);
	controles.setOrigin(controles.getGlobalBounds().width/2.0f, controles.getGlobalBounds().height/2.0f);
	controles.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/10.f);
	
	up.setFont(fuente);
	up.setString("Presione ^ para saltar (y nuevamente para salto doble)");
	up.setCharacterSize(32);
	up.setFillColor(Color::Red);
	up.setOrigin(up.getGlobalBounds().width/2.0f, up.getGlobalBounds().height/2.0f);
	up.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.6f);
	
	right.setFont(fuente);
	right.setString("Presione -> para moverse a la derecha");
	right.setCharacterSize(32);
	right.setFillColor(Color::Red);
	right.setOrigin(right.getGlobalBounds().width/2.0f, right.getGlobalBounds().height/2.0f);
	right.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.3f);
	
	left.setFont(fuente);
	left.setString("Presione <- para moverse a la izquierda");
	left.setCharacterSize(32);
	left.setFillColor(Color::Red);
	left.setOrigin(left.getGlobalBounds().width/2.0f, left.getGlobalBounds().height/2.0f);
	left.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/2.f);
	
	freeze.setFont(fuente);
	freeze.setString("Presione la tecla F para ralentizar el tiempo");
	freeze.setCharacterSize(32);
	freeze.setFillColor(Color::Red);
	freeze.setOrigin(freeze.getGlobalBounds().width/2.0f, freeze.getGlobalBounds().height/2.0f);
	freeze.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.7f);
	
	god.setFont(fuente);
	god.setString("Presione la tecla G para hacerse invencible");
	god.setCharacterSize(32);
	god.setFillColor(Color::Red);
	god.setOrigin(god.getGlobalBounds().width/2.0f, god.getGlobalBounds().height/2.0f);
	god.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.5f);
	
	
	volver.setFont(fuente);
	volver.setString("Presione la tecla Z nuevamente para volver al menu");
	volver.setCharacterSize(32);
	volver.setFillColor(Color::White);
	volver.setOrigin(volver.getGlobalBounds().width/2.0f, volver.getGlobalBounds().height/2.0f);
	volver.setPosition(wnd->getSize().x/2.0f, wnd->getSize().y/1.1f);
}

Controles::~Controles() { }

void Controles::Actualizar(float dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
		_game->CambiarEscena(new Menu(_game, _wnd));
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		_wnd->close();
}

void Controles::Dibujar() 
{ 
	_wnd->clear(Color::Black);
	_wnd->draw(controles);
	_wnd->draw(up);
	_wnd->draw(right);
	_wnd->draw(left);
	_wnd->draw(freeze);
	_wnd->draw(god);
	_wnd->draw(volver);
	
	_wnd->display();
}

void Controles::ProcesarEventos() 
{
	sf::Event e;
	while (_wnd->pollEvent(e))
	{
		if (e.type == Event::Closed)
			_wnd->close();
	}
}

void Controles::ProcesarColisiones() { }
