#pragma once
#include "GameObject.h"

// bullet inherited from GameObject
class Bullet : public GameObject
{
public:
	using GameObject::GameObject;
	
	void Update();

private:
};

