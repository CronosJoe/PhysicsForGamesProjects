#include "baseGame.h"
#include "demoGame.h"
#include "physicsObject.h"

int main()
{
	baseGame* game = new demoGame();
	game->init();
	while(!game->shouldClose()) //while the game screen is open
	{
		game->tick();
		game->draw();
	}

	game->exit();

	delete game;

	return 0;
}