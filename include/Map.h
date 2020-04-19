#pragma once
#include "Game.h"

// might remove this class, not sure yet. should never need to be interacted with

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[20][25]);

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



	int map[20][25];

};

