#pragma once 
#include<raylib.h>

class Alien {

public:

	Alien(int type, Vector2 position);
	void Draw();
	void Update(int direction);
	int GetType();
	Rectangle getRect();
	static void UnloadImages();
	static Texture2D alienImages[3];
	Vector2 position;
	int type;

private:








};