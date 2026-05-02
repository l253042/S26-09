#pragma once 
#include<raylib.h>

class Alien {

public:

	Alien(int type, Vector2 position);
	void Draw();
	void Update();
	int GetType();
	Texture2D image;
	Vector2 position;
	int type;

private:








};