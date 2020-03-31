#include "Game.h"

// initializing the renderer, the map, and any other Player objects
SDL_Renderer* Game::renderer = nullptr;
Map* map = nullptr;
Player* red = nullptr;
Player* blue = nullptr;
GameObject* Game::redflag = nullptr;
GameObject* Game::blueflag = nullptr;

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

	// constructor for all main rendered objects
	red = new Player("../Assets/pone.png", 100 , height/2 - 55, "red");
	blue = new Player("../Assets/ptwo.png", width - 108, height/2 - 55, "blue");
	redflag = new GameObject("../Assets/redflag.png", 15, height / 2 - 25, "red");
	blueflag = new GameObject("../Assets/blueflag.png", width - 50, height / 2 - 25, "blue");
	
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

		//Handle input for the players
		red->handleEvent(event);
		blue->handleEvent(event);
	}
}

// when update is called, we then call the update function of every object within our Game that needs to be updated
void Game::update()
{
	// update red
	red->Update();

	// if red dies, spawn a barrier on its death location and push it to the vector of red barriers
	if (redHealth == 0)
	{
		std::cout << "left rectangle died" << std::endl;
		Player barrier = *red;
		redbarriers.push_back(barrier);
		redHealth = 100;
	}

	//update blue
	blue->Update();

	// if blue dies, spawn a barrier on its death location and push it to the vector of blue barriers
	if (blueHealth == 0)
	{
		Player barrier = *blue;
		bluebarriers.push_back(barrier);
		std::cout << "right rectangle died" << std::endl;
		blueHealth = 100;
	}

	// iterate through all red barriers and destroy if their health is 0
	for (auto& x : redbarriers)
	{
		if (x.getHealth() == 0)
		{
			x.die();
		}
	}

	// iterate through all red barriers and destroy if their health is 0
	for (auto& x : bluebarriers)
	{
		if (x.getHealth() == 0)
		{
			x.die();
		}
	}

	// update state of flags
	blueflag->Update();
	redflag->Update();
}

// render sets up other objects to be rendered , and then calls the render function of other objects
void Game::render()
{
	// pre render call
	SDL_RenderClear(renderer);

	map->DrawMap();
	redflag->Render();
	blueflag->Render();
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

	// post render call
	SDL_RenderPresent(renderer);
}

// clean uses SDL functions to free allocated resources, we also call delete on other object pointers
void Game::clean()
{
	delete map;
	delete red;
	delete blue;
	delete redflag;
	delete blueflag;
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
