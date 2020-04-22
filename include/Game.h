#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "TextureManager.h"
#include "Map.h"


// the Game class holds everything actually present in the game loop
class Game
{
	public:
		Game();
		~Game();

		// initialize creates the renderer, the window we render to, and any GameObjects
		void initialize(const char* word, int xpos, int ypos, int width, int height, bool fullscreen);

		// handles inputs
		void handleEvents();

		// called to update the state of everyting inside Game
		void update();

		// called to render everything after updating
		void render();

		// called in destructor, frees SDL entities and deletes object pointers
		void clean();

		// returns isRunning
		int running();

		// allows our renderer to be accesible to all objects inside the Game class
		static SDL_Renderer* renderer;
		
		// provides global access to the hitboxes of the players
		static SDL_Rect redHit;
		static SDL_Rect blueHit;

		// provides global access for player health, can fix later 
		static int redHealth;
		static int blueHealth;

		// provides global access to all barriers
		static std::vector<Player> redbarriers;
		static std::vector<Player> bluebarriers;

		// provides global access to red and blue flags
		static GameObject* redflag;
		static GameObject* blueflag;

		static int bluescore;
		static int redscore;

		static GameObject* redbase;
		static GameObject* bluebase;


		static bool spawnred;
		static bool spawnblue;
	private:
		// counts frames 
		int counter = 0;
		SDL_Texture* scorerender;
		// whether or not the game is running, set to false to exit
		int isRunning;

		// the window our Game renders to
		SDL_Window* window;

		

};
