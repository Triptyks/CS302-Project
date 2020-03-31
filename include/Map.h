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
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];

};

