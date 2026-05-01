#include"game.hpp"
#include<iostream>
using namespace std;

Game::Game() {

	obstacles = CreateObstacles();

}

Game::~Game() {

}
void Game::Update() {

	for (int i = 0; i < spaceship.lasers.size(); i++) {
		spaceship.lasers[i].Update();
	}
	DeleteInactiveLasers();
	

}

void Game::Draw() {
	spaceship.Draw();

	for (int i = 0; i < spaceship.lasers.size(); i++) {
		spaceship.lasers[i].Draw();
	}
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Draw();
	}

}

void Game::HandleInput() {

	if (IsKeyDown(KEY_LEFT)) {
		spaceship.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		spaceship.MoveRight();
	}
	else if (IsKeyDown(KEY_SPACE)) {
		spaceship.FireLaser();
	}
}

void Game::DeleteInactiveLasers() {

	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
		if (!it->active) {
			it = spaceship.lasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles() {

	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5; 
	//Creates equal spacing between obstacles 
	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX,float(GetScreenHeight() - 150) }));
	}
	return obstacles;

}