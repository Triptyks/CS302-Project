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

	// redefining GameObject functions to do specific things for a player
	void Update();
	void Render();

	// shoot is called to fire a bullet
	void Shoot(); 

	// subtracts health by 25
	void takeDamage(int dmg);

	// returns health
	int getHealth();

	// convert to private later
	bool hasFlag = false;
	int points = 0;
	
	void reset();

private:
	int movevelocity = 20;
	int health = 100;
	std::vector<Bullet*> bullets;
	bool isShooting = false;
};

