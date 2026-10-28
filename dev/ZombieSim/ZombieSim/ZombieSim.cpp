#include <cstdlib>
#include <ctime>
#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));	// seed once, up front

	Game game;
	game.Run();

	return 0;
}
