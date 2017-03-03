#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
    game.AddInputMappings();
    
	if (game.Init())
	{
		game.RunLoop();
	}

	return 0;
}
