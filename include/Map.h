#pragma once
#include "Game.h"

// class used to draw the background with modular tiles

class Map
{
public:

	Map();
	~Map();

	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* tile;
	SDL_Texture* tile2;
	SDL_Texture* tiledark;
	SDL_Texture* tile2dark;

	SDL_Texture* tilered;
	SDL_Texture* tile2red;
	SDL_Texture* tileblue;
	SDL_Texture* tile2blue;

	SDL_Texture* one;
	SDL_Texture* two;
	SDL_Texture* three;
	SDL_Texture* four;
	SDL_Texture* five;

	SDL_Texture* score;

};

