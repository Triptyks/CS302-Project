#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"


// the Game class holds everything actually present in the game loop
class Game
{
	public:
		Game();
		~Game();


		// initialize creates the renderer, the window we render to, and creates high scoped GameObjects
		void initialize(const char* word, int xpos, int ypos, int width, int height, bool fullscreen);

		// currently handles the input for x'ing out of the window
		void handleEvents();

		// called to update the state of everyting inside Game
		void update();

		// called to render everything after updating
		void render();

		// called in destructor, frees SDL entities and deletes object pointers
		void clean();

		// returns isRunning
		bool running();

		// allows our renderer to be accesible to all objects inside the Game class
		static SDL_Renderer* renderer;
		
		static SDL_Rect redHit;
		static SDL_Rect blueHit;

		static int redHealth;
		static int blueHealth;

		static std::vector<Player> redbarriers;
		static std::vector<Player> bluebarriers;

	private:
		// counts frames 
		int counter = 0;

		// whether or not the game is running, set to false to exit
		bool isRunning;

		// the window our Game renders to
		SDL_Window* window;

		

};
