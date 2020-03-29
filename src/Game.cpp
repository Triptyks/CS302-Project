#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

SDL_Renderer* Game::renderer = nullptr;
Map* map = nullptr;

GameObject* player = nullptr;
GameObject* foe = nullptr;


Game::Game()
{}
Game::~Game()
{
	clean();
}

void Game::initialize(const char* word, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(word, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}

	player = new GameObject("../Assets/line.png", 0 , 0);
	foe = new GameObject("../Assets/foe.png", 50, 50);
	map = new Map();

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	player->Update();
	foe->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	foe->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	delete map;
	delete foe;
	delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game cleaned" << std::endl;
}

bool Game::running()
{
	return isRunning;
}



