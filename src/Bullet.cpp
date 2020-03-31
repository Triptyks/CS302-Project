#include "Game.h"
#include "Bullet.h"

void Bullet::Update()
{
	// bullets go right to left if you are red and left to right if you are blue
	// later we want bullets to fire from your front as you rotate
	if (player == "blue")
	{
		xpos -= 10;
	}
	else
	{
		xpos += 10;
	}
	ypos += 0;



	// rectangle stuff
	srcRect.h = 5;
	srcRect.w = 5;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;


	// if red is hit, we "delete" the bullet and subtract health
	if (SDL_HasIntersection(&Game::redHit, &destRect))
	{
		std::cout << "left rectangle hit" << std::endl;
		xpos = 10000;
		ypos = 10000;
		
		Game::redHealth -= 20;
	}

	// if blue is hit, we "delete" the bullet and subtract health
	if (SDL_HasIntersection(&Game::blueHit, &destRect))
	{
		std::cout << "right rectangle hit" << std::endl;
		xpos = 10000;
		ypos = 10000;

		Game::blueHealth -= 20;
	}
	
	// iterating through every red barrier
	for (auto& x: Game::redbarriers)
	{
		// checking if we collide with a barrier
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			// if a red bullet hits a red barrier, subtract from barrier health and remove bullet
			if (player == "red")
			{
				x.takeDamage();
				xpos = 10000;
				ypos = 10000;
				//die();
			}
			// if a red bullet hits a blue barrier, remove bullet only
			else
			{
				xpos = 10000;
				ypos = 10000;
				//die();
			}
		}
	}

	// iterating through every blue barrier
	for (auto &x : Game::bluebarriers)
	{
		// checking if we collide with a barrier
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			// if a blue bullet hits a red barrier, remove bullet only
			if (player == "red")
			{
				xpos = 10000;
				ypos = 10000;
				//die();
			}
			// if a blue bullet hits a blue barrier, subtract from barrier health and remove bullet
			else
			{
				x.takeDamage();
				xpos = 10000;
				ypos = 10000;
				//die();
			}
		}
	}
	
}
