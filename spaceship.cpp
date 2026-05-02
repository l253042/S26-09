#include "spaceship.hpp"


Spaceship::Spaceship()
{
	image = LoadTexture("Graphics/spaceship1.png");
	position.x = (GetScreenWidth() - image.width * scale) / 2;
	position.y = GetScreenHeight() - image.height * scale;
	lastFireTime = 0.0;
};

Spaceship::~Spaceship() {

	UnloadTexture(image);

}

void Spaceship::Draw() {

	DrawTextureEx(image, position, 0.0f, scale, WHITE);
}

void Spaceship::MoveLeft() {
	position.x -= 5;
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::MoveRight() {
	position.x += 5;
	if (position.x > (GetScreenWidth() - image.width * scale)) {
		position.x = (GetScreenWidth() - image.width * scale );
	}
}

void Spaceship::FireLaser() {
	
	if (GetTime() - lastFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width * scale / 2 - 2,position.y }, -6));
		lastFireTime = GetTime();
	
	}
}

Rectangle Spaceship::getRect() {


	return{ position.x,position.y,float(image.width),float(image.height) };


}