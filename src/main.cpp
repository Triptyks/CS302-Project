#include "Game.h"

// where the actual game loop is handled
Game* game = nullptr;

int main(int argc, char *argv[])
{
	// fps information
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// creates a new Game
	game = new Game();
	game->initialize("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, false);
	
	// the game loop
	while(game->running())
	{
		frameStart = SDL_GetTicks();

		// handles events, updates, and renders the Game
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();

	return 0;
}