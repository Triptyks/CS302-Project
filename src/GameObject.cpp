#include "GameObject.h"
#include "TextureManager.h"

// initializes the GameObject's texture, positions, and velocities
GameObject::GameObject(const char* texturesheet, int x, int y, std::string pcolor, int velocity)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;

	xvel = 0;
	yvel = 0;

	player = pcolor;

	velo = velocity;
}

// currently empty destructor
GameObject::~GameObject()
{

}


// called to update the object's positions and it's rendering rectangle's position
void GameObject::Update()
{
	xpos += xvel;
	ypos += yvel;
	srcRect.h = 48;
	srcRect.w = 48;
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

// returns flags to their spawn positions, later will use objects stored "spawn" points
void GameObject::alive()
{
	if (player == "red")
	{
		xpos = 15;
		ypos = 600 / 2 - 25;
		
	}
	else
	{
		xpos = 800 - 60;
		ypos = 600 / 2 - 25;
	}

	destRect.x = xpos;
	destRect.y = ypos;
}

// "kills" an object
void GameObject::die()
{
	xpos = 10000;
	ypos = 10000;
	destRect.x = xpos;
	destRect.y = ypos;
}
