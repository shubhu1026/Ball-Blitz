#include "Game.h"

int main()
{
	//Initialize random seed
	srand(static_cast<unsigned>(time(0)));

	//Init Game	Object
	Game game;
	
	//Game Loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}