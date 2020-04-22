#include "Player.h"
#include "Game.h"

// destructor deletes the vector of Bullet pointers 
Player::~Player()
{
	for (auto x : bullets)
	{
		delete x;
	}
}

void Player::handleEvent(SDL_Event& e)
{
	//handles events for the ble player
	if (player == "blue")
	{
		// if key press down
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//handles direction velocity and shoot
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yvel -= movevelocity; break;
			case SDLK_DOWN: yvel += movevelocity; break;
			case SDLK_LEFT: xvel -= movevelocity; break;
			case SDLK_RIGHT: xvel += movevelocity; break;
			case SDLK_PERIOD: Shoot(); break;
			case SDLK_SLASH: Game::spawnblue = true; break;
			}

			lastdir = velo;
		}
		// if key release
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{

			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yvel += movevelocity; break;
			case SDLK_DOWN: yvel -= movevelocity; break;
			case SDLK_LEFT: xvel += movevelocity; break;
			case SDLK_RIGHT: xvel -= movevelocity; break;
			}

			lastdir = velo;
		}
	}
	// same as above but different controls for red
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yvel -= movevelocity; break;
			case SDLK_s: yvel += movevelocity; break;
			case SDLK_a: xvel -= movevelocity; break;
			case SDLK_d: xvel += movevelocity; break;
			case SDLK_c: Shoot(); break;
			case SDLK_v: Game::spawnred = true; break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yvel += movevelocity; break;
			case SDLK_s: yvel -= movevelocity; break;
			case SDLK_a: xvel += movevelocity; break;
			case SDLK_d: xvel -= movevelocity; break;
			}
		}
	}
}

// shoot creates a new bullet
void Player::Shoot()
{
	Bullet* newbullet;

	if (xvel > 0)
	{
		newbullet = new Bullet("../Assets/bullet.png", xpos + 10, ypos + 55, player, xvel);
	}
		
	if (xvel == 0)
	{
		if (player == "red")
		{
			newbullet = new Bullet("../Assets/bullet.png", xpos + 5, ypos + 55, player, xvel);
		}
		else
		{
			newbullet = new Bullet("../Assets/bullet.png", xpos - 5, ypos + 55, player, xvel);
		}
	}
	
	if(xvel < 0)
	{
		 newbullet = new Bullet("../Assets/bullet.png", xpos - 10, ypos + 55, player, xvel);
	}
	
	bullets.push_back(newbullet);
}

// all updates needed for the player
void Player::Update()
{
	// updating the position of all bullets that belong to the player
	for (auto x : bullets)
	{
		x->Update();
	}

	// position change from input and SDL_Rect stuff
	xpos += xvel;

	//If the dot went too far to the left or right
	if ((xpos < 0) || (xpos + 10 > 800))
	{
		//Move back
		xpos -= xvel;
	}




	ypos += yvel;

	//If the dot went too far to the left or right
	if ((ypos < 0) || (ypos + 125 > 600))
	{
		//Move back
		ypos -= yvel;
	}

	srcRect.h = 125;
	srcRect.w = 10;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	
	// updating the global hitboxes for red and blue
	if (player == "blue")
	{
		Game::blueHit = destRect;
	}
	else
	{
		Game::redHit = destRect;
	}


	if (Game::blueHealth == 0 && player == "blue" || Game::spawnblue == true && player == "blue")
	{
		reset();
	}

	if (Game::redHealth == 0 && player == "red" || Game::spawnred == true && player == "red")
	{
		reset();
	}


	// checks if collision needs to be applied and applies it with -xvel;
	for (auto x : Game::redbarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			xpos -= xvel;
		}

	}

	// same but for blue barriers
	for (auto x : Game::bluebarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			xpos -= xvel;
		}


	}

	// if red goes over blue flag, pick it up and change to flag carrying texture
	if (SDL_HasIntersection(&Game::blueflag->getBox(), &destRect) && player == "red")
	{
		Game::blueflag->die();
		objTexture = TextureManager::LoadTexture("../Assets/poneflag.png");
		hasFlag = true;
	}

	// if red caps the blue flag, respawn blue flag, set original texture, and increment poitns
	if (SDL_HasIntersection(&Game::redbase->getBox(), &destRect) && player == "red" && hasFlag == true)
	{
		Game::blueflag->alive();
		objTexture = TextureManager::LoadTexture("../Assets/pone.png");
		hasFlag = false;
		points++;
		std::cout << "Red scored, red now has " << Game::redscore << " points. "  << std::endl;
		Game::redscore++;
	}

	// if blue goes over red flag, pick it up and change to flag carrying texture
	if (SDL_HasIntersection(&Game::redflag->getBox(), &destRect) && player == "blue")
	{
		Game::redflag->die();
		objTexture = TextureManager::LoadTexture("../Assets/ptwoflag.png");
		hasFlag = true;
	}

	// if blue caps the red flag, respawn blue flag, set original texture, and increment poitns
	if (SDL_HasIntersection(&Game::bluebase->getBox(), &destRect) && player == "blue" && hasFlag == true)
	{
		Game::redflag->alive();
		objTexture = TextureManager::LoadTexture("../Assets/ptwo.png");
		hasFlag = false;
		points++;
		Game::bluescore++;
		std::cout << "Blue scored, blue now has " << Game::bluescore << " points. " << std::endl;
	}

	if (SDL_HasIntersection(&Game::redHit, &destRect) && player == "blue")
	{
		xpos -= xvel;
	}

	if (SDL_HasIntersection(&Game::blueHit, &destRect) && player == "red")
	{
		xpos -= xvel;
	}


}


void Player::Render()
{
	// renders every bullet belonging to the player
	for (auto x : bullets)
	{
		x->Render();
	}

	// takes the renderer, the texture, the source rectangle, and the destination rectangle
	// the source rectangle defines what portion of our image texture we render from
	// the destination rectangle defines where the texture taken from the source rectangle is rendered to 
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

// called when player is hit by bullet
void Player::takeDamage(int dmg)
{
	std::cout << "health went from " << health << " to ";
	health -=dmg;
	std::cout << health << std::endl;
}

// returns player health
int Player::getHealth()
{
	return health;
}


void Player::reset()
{
	// if the blue's health is 0, we set it to default state and respawn it
	if (player == "blue")
	{
		bullets.clear();
		objTexture = TextureManager::LoadTexture("../Assets/ptwo.png");
		xpos = 800 - 108;
		ypos = 600 / 2 - 55;

		// if the player died with flag, respawn the flag, later can make to drop on death location
		if (hasFlag == true)
		{
			Game::redflag->alive();
			hasFlag = false;
		}
	}

	// if red dies, default state and respawn red
	if (player == "red")
	{
		bullets.clear();
		objTexture = TextureManager::LoadTexture("../Assets/pone.png");
		xpos = 100;
		ypos = 600 / 2 - 55;

		// returns flag if red dies with it
		if (hasFlag == true)
		{
			Game::blueflag->alive();
			hasFlag = false;
		}
	}

}




void Player::Barrier()
{

	if (player == "red")
	{

		objTexture = TextureManager::LoadTexture("../Assets/ponebarrier.png");

		Player barrier = *this;
		Game::redbarriers.push_back(barrier);

		objTexture = TextureManager::LoadTexture("../Assets/pone.png");
		Game::redHealth = 100;
	}

	if (player == "blue")
	{

		objTexture = TextureManager::LoadTexture("../Assets/ptwobarrier.png");

		Player barrier = *this;
		Game::bluebarriers.push_back(barrier);

		objTexture = TextureManager::LoadTexture("../Assets/ptwo.png");
		Game::blueHealth = 100;
	}


}

