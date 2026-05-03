#include "spaceship.hpp"


Spaceship::Spaceship()
{
	image = LoadTexture("Graphics/spaceship1.png");
	position.x = (GetScreenWidth() - image.width * scale) / 2;
	position.y = (GetScreenHeight() - image.height * scale)-60;
	lastFireTime = 0.0;
	isHit = false;
	hitTime = 0;
	laserSound = LoadSound("Sounds/laser.ogg");
};

Spaceship::~Spaceship() {

	UnloadTexture(image);
	UnloadSound(laserSound);

}

void Spaceship::Draw() {
	
	if (isHit) {
		if ((int)(GetTime() * 10) % 2 == 0) {  
			DrawTextureEx(image, position, 0.0f, scale, WHITE);
		}
		if (GetTime() - hitTime >= 2.0f) { 
			isHit = false;
		}
	}
	else {
		DrawTextureEx(image, position, 0.0f, scale, WHITE);
	}
}

void Spaceship::MoveLeft() {
	position.x -= 5;
	if (position.x < 25) {
		position.x = 25;
	}
}

void Spaceship::MoveRight() {
	position.x += 5;
	if (position.x > (GetScreenWidth() - image.width * scale - 25)) {
		position.x = (GetScreenWidth() - image.width * scale -25 );
	}
}

void Spaceship::FireLaser() {
	
	if (GetTime() - lastFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width * scale / 2 - 2,position.y }, -6));
		lastFireTime = GetTime();
		PlaySound(laserSound);
	
	}
}

Rectangle Spaceship::getRect() {


	return{ position.x,position.y,float(image.width) * scale,float(image.height)*scale };
}

void Spaceship::Reset() {

	position.x = (GetScreenWidth() - image.width * scale) / 2.0f;
	position.y = (GetScreenHeight() - image.height * scale)- 60;
	lasers.clear();
	isHit = false;
	hitTime = 0;
}