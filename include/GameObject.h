#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// the GameObject class represents any entity that we need to update/render inside the game itself

class GameObject
{

public:
	// constructor takes the objects texture and the coordinates to render the object to
	GameObject(const char* texturesheet, int x, int y, std::string pcolor);
	~GameObject();

	// update and render functions
	void Update();
	void Render();
	SDL_Rect getBox();

protected:
	int xpos,ypos;
	int xvel,yvel;
	std::string player;

	// the objects texture, and rendering Rectangles
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

	
	
	//SDL_Renderer* renderer;
};



