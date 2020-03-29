#pragma once
#include "Game.h"

// map represents a tileable background renderer, going to ignore this for not cause its not important for the game

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

