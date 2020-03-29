#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class Game
{
	public:
		Game();
		~Game();

		void initialize(const char* word, int xpos, int ypos, int width, int height, bool fullscreen);
		
		void handleEvents();
		void update();
		void render();
		void clean();

		bool running();

		static SDL_Renderer* renderer;

	private:
		int counter = 0;
		bool isRunning;
		SDL_Window* window;
};

