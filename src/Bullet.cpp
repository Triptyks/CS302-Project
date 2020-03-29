#include "Game.h"
#include "Bullet.h"

void Bullet::Update()
{
	//travelled += 10;
	if (player == "blue")
	{
		xpos -= 10;
	}
	else
	{
		xpos += 10;
	}
	ypos += 0;


	srcRect.h = 5;
	srcRect.w = 5;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;


	if (SDL_HasIntersection(&Game::redHit, &destRect))
	{
		std::cout << "left rectangle hit" << std::endl;
		xpos = 10000;
		ypos = 10000;
		
		Game::redHealth -= 20;
	}

	if (SDL_HasIntersection(&Game::blueHit, &destRect))
	{
		std::cout << "right rectangle hit" << std::endl;
		xpos = 10000;
		ypos = 10000;

		Game::blueHealth -= 20;
	}
//                      FUNCTIONIFTY THIS FUNCTION THSI FUNCTION THIS FUNCTION THIS FUNCTION THIS
	for (auto& x: Game::redbarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			if (player == "red")
			{
				std::cout << "a red bullet hit a red barrier" << std::endl;
				x.takeDamage();
				xpos = 10000;
				ypos = 10000;
			}
			else
			{
				std::cout << "a blue bullet hit a red barrier" << std::endl;
				xpos = 10000;
				ypos = 10000;
			}
		}
	}

	for (auto &x : Game::bluebarriers)
	{
		if (SDL_HasIntersection(&x.getBox(), &destRect))
		{
			if (player == "red")
			{
				std::cout << "a red bullet hit a blue barrier" << std::endl;
				
				xpos = 10000;
				ypos = 10000;
			}
			else
			{
				std::cout << "a blue bullet hit a blue barrier" << std::endl;
				x.takeDamage();
				xpos = 10000;
				ypos = 10000;
			}
		}
	}
	
}
