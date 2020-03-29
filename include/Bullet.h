#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	using GameObject::GameObject;
	
	void Update();

private:
	//int travelled = 0;
};

