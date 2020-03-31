#include "GameObject.h"
#include "TextureManager.h"

// initializes the GameObject's texture, positions, and velocities
GameObject::GameObject(const char* texturesheet, int x, int y, std::string pcolor)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;

	xvel = 0;
	yvel = 0;

	player = pcolor;
}

// currently empty destructor
GameObject::~GameObject()
{

}


// called to update the object's positions and it's rendering rectangle's position, currently moves 1 x and 1 y per frame
void GameObject::Update()
{
	xpos += xvel;
	ypos += yvel;
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

// called to render the object using render copy
void GameObject::Render()
{
	// takes the renderer, the texture, the source rectangle, and the destination rectangle
	// the source rectangle defines what portion of our image texture we render from
	// the destination rectangle defines where the texture taken from the source rectangle is rendered to 
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

SDL_Rect GameObject::getBox()
{
	return destRect;
}



// returns flags to their spawn positions
void GameObject::alive()
{
	if (player == "red")
	{
		xpos = 15;
		ypos = 400 /2 - 25;
		
	}
	else
	{
		xpos = 800 - 50;
		ypos = 400 /2 - 25;
	}

	destRect.x = xpos;
	destRect.y = ypos;
}


void GameObject::die()
{
	xpos = 10000;
	ypos = 10000;
	destRect.x = xpos;
	destRect.y = ypos;
}
