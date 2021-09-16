#include "baseGame.h"
#include "demoGame.h"

int main()
{
	baseGame* game = new demoGame();
	game->init();
	while(!game->shouldClose())
	{
		game->tick();
		game->draw();
	}

	game->exit();

	delete game;

	return 0;
}