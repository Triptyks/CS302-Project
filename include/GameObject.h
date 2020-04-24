#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// the GameObject class represents any entity that we need to update/render inside the game itself

class GameObject
{

public:
	// constructor takes the objects texture, coordinates to render the object to, and its color
	GameObject(const char* texturesheet, int x, int y, std::string pcolor, int velocity);
	~GameObject();

	// update and render functions
	void Update();
	void Render();

	// returns an SDL_Rect, usually for collision testing
	SDL_Rect getBox();

	// returns object to spawn, currently only use on the flags, will fix later
	void alive();

	// sends object to very far away coordinates off screen
	void die();

	SDL_Texture* objTexture;

	// info about position
	int xpos, ypos;
	int xvel, yvel;

	//rectangle for rendering / collision
	SDL_Rect srcRect, destRect;
protected:
	
	// red or blue
	std::string player;

	// velocity and last faced direction
	int velo;
	int lastdir;
};



