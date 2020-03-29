#pragma once
#include "GameObject.h"
#include "Bullet.h"

// player class inherited from GameObject, adds some player specific functions
class Player : public GameObject
{

public:
	// inherits the old constructor
	using GameObject::GameObject;
	~Player();

	
	// handles events specific to the Player
	void handleEvent(SDL_Event& e);

	void Shoot();
	void Update();
	void Render();

private:
	std::vector<Bullet*> bullets;
	bool isShooting = false;
};

