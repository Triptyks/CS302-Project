#include "Bullet.h"


void Bullet::Update()
{
	//travelled += 10;
	if (player == 0)
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

	/*
	if (travelled >= 50)
	{
		delete this;
	}
	*/
}
