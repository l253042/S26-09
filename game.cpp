#include"game.hpp"
#include<iostream>
using namespace std;

Game::Game() {

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