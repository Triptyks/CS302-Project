#pragma once
#include "GameObject.h"
#include "Bullet.h" 
#include <vector>
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
	void takeDamage();
	int getHealth();
	bool hasFlag = false;
	int points = 0;
	//void die();

private:
	
	int health = 100;
	std::vector<Bullet*> bullets;
	bool isShooting = false;
};

