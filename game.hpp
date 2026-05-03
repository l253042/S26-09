#pragma once
#include<string>
#include"spaceship.hpp"
#include"obstacle.hpp"
#include"alien.hpp"
#include"mysteryship.hpp"

class Game {

public:

	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	bool run;
	enum GameState { STARTING, RUNNING, PAUSED, GAMEOVER, LEVELUP, GAMECOMPLETED };
	GameState state;
	int level;
	float levelUpTime;
	int lives;
	int score;
	int highscore;
	Music music;

private:

	Spaceship spaceship;
	std::vector<Obstacle>CreateObstacles();
	std::vector<Alien>CreateAliens();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	void CheckForCollisions();
	void DeleteInactiveLasers();
	void GameOver();
	void Reset();
	void InitGame();
	void checkForHighscore();
	void saveHighscoreToFile(int highscore);
	int loadHighscoreFromFile();
	std::vector<Obstacle>obstacles;
	std::vector<Alien>aliens;
	int aliensDirection;
	std::vector<Laser>alienLasers;
	float alienLaserShootInterval = 0.35;
	float timeLastAlienFired;
	MysteryShip mysteryship;
	float mysteryShipSpawnInterval;
	float timeLastSpawn;
	Sound explosionSound;
	Sound spaceshipExplosion;
	struct ScorePopup {
		Vector2 position;
		std::string text;
		float spawnTime;
		bool active;
	};
	std::vector<ScorePopup> scorePopups;
	

};