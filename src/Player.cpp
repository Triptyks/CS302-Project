#include "Player.h"
#include "Game.h"

Player::~Player()
{/*
	for (auto x : bullets)
	{
		delete x;
	}
	*/
}

void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (player == "blue")
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yvel -= 3; break;
			case SDLK_DOWN: yvel += 3; break;
			case SDLK_LEFT: xvel -= 3; break;
			case SDLK_RIGHT: xvel += 3; break;
			case SDLK_PERIOD: Shoot(); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yvel += 3; break;
			case SDLK_DOWN: yvel -= 3; break;
			case SDLK_LEFT: xvel += 3; break;
			case SDLK_RIGHT: xvel -= 3; break;
			}
		}
	}
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yvel -= 3; break;
			case SDLK_s: yvel += 3; break;
			case SDLK_a: xvel -= 3; break;
			case SDLK_d: xvel += 3; break;
			case SDLK_c: Shoot(); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yvel += 3; break;
			case SDLK_s: yvel -= 3; break;
			case SDLK_a: xvel += 3; break;
			case SDLK_d: xvel -= 3; break;
			}
		}
	}
}

void Player::Shoot()
{

	Bullet* newbullet = new Bullet("../Assets/bullet.png", xpos, ypos + 20, player);
	bullets.push_back(newbullet);
}

void Player::Update()
{
	for (auto x : bullets)
	{
		x->Update();
	}

	xpos += xvel;
	ypos += yvel;
	srcRect.h = 100;
	srcRect.w = 8;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;


	if (player == "blue")
	{
		Game::blueHit = destRect;
	}
	else
	{
		Game::redHit = destRect;
	}

	if (Game::blueHealth == 0 && player == "blue")
	{
		objTexture = TextureManager::LoadTexture("../Assets/ptwo.png");
		xpos = 800 - 108;
		ypos = 400 / 2 - 55;

		if (hasFlag == true)
		{
			Game::redflag->alive();
			hasFlag = false;
		}
	}

	if (Game::redHealth == 0 && player == "red")
	{
		objTexture = TextureManager::LoadTexture("../Assets/pone.png");
		xpos = 100;
		ypos = 400 / 2 - 55;
		
		if (hasFlag == true)
		{
			Game::blueflag->alive();
			hasFlag = false;
		}
	}

	for (auto x : Game::redbarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			xpos -= xvel;
		}
	}

	for (auto x : Game::bluebarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			xpos -= xvel;
		}
	}

	// if red goes over blue flag
	if (SDL_HasIntersection(&Game::blueflag->getBox(), &destRect) && player == "red")
	{
		Game::blueflag->die();
		objTexture = TextureManager::LoadTexture("../Assets/poneflag.png");
		hasFlag = true;
	}

	// if red caps the blue flag
	if (SDL_HasIntersection(&Game::redflag->getBox(), &destRect) && player == "red" && hasFlag == true)
	{
		Game::blueflag->alive();
		objTexture = TextureManager::LoadTexture("../Assets/pone.png");
		hasFlag = false;
		points++;
		std::cout << "Red scored, red now has" << points << " points. "  << std::endl;
	}

	// if blue goes over red flag
	if (SDL_HasIntersection(&Game::redflag->getBox(), &destRect) && player == "blue")
	{
		Game::redflag->die();
		objTexture = TextureManager::LoadTexture("../Assets/ptwoflag.png");
		hasFlag = true;
	}

	// if blue caps red flag
	if (SDL_HasIntersection(&Game::blueflag->getBox(), &destRect) && player == "blue" && hasFlag == true)
	{
		Game::redflag->alive();
		objTexture = TextureManager::LoadTexture("../Assets/ptwo.png");
		hasFlag = false;
		points++;
		std::cout << "Blue scored, blue now has" << points << " points. " << std::endl;
	}
}


void Player::Render()
{

	for (auto x : bullets)
	{
		x->Render();
	}

	// takes the renderer, the texture, the source rectangle, and the destination rectangle
	// the source rectangle defines what portion of our image texture we render from
	// the destination rectangle defines where the texture taken from the source rectangle is rendered to 
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void Player::takeDamage()
{
	std::cout << "health went from " << health << " to ";
	health -=20;
	std::cout << health << std::endl;
}

int Player::getHealth()
{
	return health;
}

/*
void Player::die()
{
	xpos = 10000;
	ypos = 10000;
	destRect.x = xpos;
	destRect.y = ypos;
}
*/


