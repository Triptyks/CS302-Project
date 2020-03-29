#include "Game.h"

// initializing the renderer, the map, and any other Player objects
SDL_Renderer* Game::renderer = nullptr;
Map* map = nullptr;
Player* red = nullptr;
Player* blue = nullptr;

SDL_Rect Game::blueHit;
SDL_Rect Game::redHit;

int Game::redHealth = 100;
int Game::blueHealth = 100;

std::vector<Player> Game::redbarriers;
std::vector<Player> Game::bluebarriers;


// currently empty constructor
Game::Game()
{}

// currently empty destructor 
Game::~Game()
{
	clean();
}

// initializes things so the Game itself can start running
void Game::initialize(const char* word, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// handles whether it's fullscreen or not
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initial check if SDL functions initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// setting the Game's window and renderer information
		window = SDL_CreateWindow(word, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		// setting render color if it was created properly
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}

	// actually assigning the values of the object entities declared earlier
	red = new Player("../Assets/pone.png", 50 , height/2 - 25, "red");
	blue = new Player("../Assets/ptwo.png", width - 50, height/2 - 25, "blue");
	//SDL_Rect Game::p0Hit = playerone->getBox();
	//SDL_Rect Game::p1Hit = playertwo->getBox();
	map = new Map();
}

// handles events input during the game loop
void Game::handleEvents()
{
	SDL_Event event;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		//Handle input for the dot
		red->handleEvent(event);
		blue->handleEvent(event);
	}
}

// when update is called, we then call the update function of every object within our Game that needs to be updated
void Game::update()
{
	red->Update();

	if (redHealth == 0)
	{
		std::cout << "left rectangle died" << std::endl;
		Player barrier = *red;
		redbarriers.push_back(barrier);
		redHealth = 100;
	}

	blue->Update();

	if (blueHealth == 0)
	{
		Player barrier = *blue;
		bluebarriers.push_back(barrier);
		std::cout << "right rectangle died" << std::endl;
		blueHealth = 100;
	}

	for (auto& x : redbarriers)
	{
		if (x.getHealth() == 0)
		{
			x.die();
		}
	}

	for (auto& x : bluebarriers)
	{
		if (x.getHealth() == 0)
		{
			x.die();
		}
	}
}

// render sets up other objects to be rendered , and then calls the render function of other objects
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	red->Render();
	blue->Render();

	for (auto x : redbarriers)
	{
		x.Render();
	}

	for (auto x : bluebarriers)
	{
		x.Render();
	}

	SDL_RenderPresent(renderer);
}

// clean uses SDL functions to free allocated resources, we also call delete on other object pointers
void Game::clean()
{
	delete map;
	delete red;
	delete blue;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game cleaned" << std::endl;
}

// returns running state
bool Game::running()
{
	return isRunning;
}
