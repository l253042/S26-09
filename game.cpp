#include"game.hpp"
#include<iostream>
using namespace std;

Game::Game() {

	
	InitGame();
}

Game::~Game() {

	Alien::UnloadImages();

}
void Game::Update() {
	
	if (run) {

		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {

			mysteryship.Spawn();
			timeLastSpawn = GetTime();
			mysteryShipSpawnInterval = GetRandomValue(10, 20);
		}

		for (int i = 0; i < spaceship.lasers.size(); i++) {
			spaceship.lasers[i].Update();
		}

		MoveAliens();
		AlienShootLaser();
		for (auto& laser : alienLasers) {
			laser.Update();
		}


		DeleteInactiveLasers();
		mysteryship.Update();
		CheckForCollisions();
	}
	else {
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	}
}

void Game::Draw() {
	spaceship.Draw();

	for (int i = 0; i < spaceship.lasers.size(); i++) {
		spaceship.lasers[i].Draw();
	}
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Draw();
	}

	for (int i = 0; i < aliens.size(); i++) {
		aliens[i].Draw();
	}

	for (int i = 0; i < alienLasers.size(); i++) {
		alienLasers[i].Draw();
	}

	mysteryship.Draw();
}

void Game::HandleInput() {

	if (run) {

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
	
	for (auto it = alienLasers.begin(); it != alienLasers.end();) {
		if (!it->active) {
			it = alienLasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles() {

	std::vector<Obstacle> temp;

	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		temp.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 180) }));
	}

	return temp;
}
std::vector<Alien> Game::CreateAliens() {

	std::vector<Alien>aliens;
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {

			int alienType;
			if (row == 0) {
				alienType = 3;
			}
			else if (row == 1 || row == 2) {
				alienType = 2;
			}
			else
				alienType = 1;

			float x = 75 + column * 55;
			float y = 100 + row * 55;
			aliens.push_back(Alien(alienType, { x,y }));

		}
	}
	return aliens;
}

void Game::MoveAliens() {
	for (auto& alien : aliens) {
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()-20) {
			aliensDirection = -1;
			MoveDownAliens(2);
			break; 
		}
		if (alien.position.x <20) {
			aliensDirection = 1;
			MoveDownAliens(2);
			break;  
		}
	}
	for (auto& alien : aliens) {
		alien.Update(aliensDirection);
	}
}

void Game::MoveDownAliens(int distance) {

	for (auto& alien : aliens) {
		alien.position.y += distance;
	}

}

void Game::AlienShootLaser() {

	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
		int randomIndex = GetRandomValue(0, (int)aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
	alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
						 alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
		timeLastAlienFired = GetTime();

	}

}

void Game::CheckForCollisions() {

	// Spaceship Lasers

	for (auto& laser : spaceship.lasers) {

		auto it = aliens.begin();
		while (it != aliens.end()) {
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
				it = aliens.erase(it);
				laser.active = false;
				break;
			}
			else {
				++it;
			}
		}
		if (!laser.active)
			continue;

		for (auto& obstacle : obstacles) {
			auto& blocks = obstacle.blocks;
			for (auto it = blocks.begin(); it != blocks.end(); ) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = blocks.erase(it);
					laser.active = false;
					break;
				}
				else {
					++it;
				}
			}
			if (!laser.active)
				break;
		}

		if (!laser.active)
			continue;

		if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
			mysteryship.alive = false;
			laser.active = false;
		}
	}

	// Alien Lasers

	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
			laser.active = false;
			lives--;
			if (lives == 0) {
				GameOver();
			}
			break;
		}
		if (!laser.active) 
			continue;

		for (auto& obstacle : obstacles) {
			auto& blocks = obstacle.blocks;
			for (auto it = blocks.begin(); it != blocks.end(); ) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}
	}

	//Alien collision with obstacles

	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
					it = obstacle.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}
		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
			GameOver();
		}
	}
}

void Game::GameOver() {

	run = false;

}

void Game::InitGame() {

	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirection = 1;
	lives = 2;
	run = true;
	timeLastAlienFired = GetTime();
	timeLastSpawn = GetTime();
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
	mysteryship.alive = false;

}

void Game::Reset() {

	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();

}