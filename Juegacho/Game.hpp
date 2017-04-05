#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics/RenderWindow>
using namespace std;


class Game {
	public:
		Game();
		void run();
		
	protected:
		void processEvents();
		void update();
		void render();
};

#endif
