#pragma once
#include"spaceship.hpp"
#include"obstacle.hpp"


class Game {

public:

	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();

private:

	Spaceship spaceship;
	std::vector<Obstacle>CreateObstacles();
	void DeleteInactiveLasers();
	std::vector<Obstacle>obstacles;

};