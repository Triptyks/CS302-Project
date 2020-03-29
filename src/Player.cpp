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

	std::cout << Game::redbarriers.size() << std::endl;
	
	for (auto x : Game::redbarriers)
	{
		std::cout << x.getHealth() << std::endl;
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
		xpos = 800 - 50;
		ypos = 400 / 2 - 25;
	}

	if (Game::redHealth == 0 && player == "red")
	{
		xpos = 50;
		ypos = 400 / 2 - 25;
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

void Player::die()
{
	xpos = 10000;
	ypos = 10000;
	destRect.x = xpos;
	destRect.y = ypos;
}


