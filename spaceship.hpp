#pragma once 
#include<raylib.h>
#include"laser.hpp"
#include<vector>



class Spaceship {

public:

	Spaceship();
	~Spaceship();
	void Update();
	void Draw();
	void MoveRight();
	void MoveLeft();
	void FireLaser();
	Rectangle getRect();
	void Reset();
	std::vector<Laser> lasers;
	bool isHit;
	float hitTime;

private:
	float scale = 0.10f;
	Texture2D image;
	Vector2 position;
	double lastFireTime;
	Sound laserSound;

};