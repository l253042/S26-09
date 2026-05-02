#include<raylib.h>
#include"game.hpp"


int main() {

	int windowWidth = 800;
	int windowHeight = 600;
	Color Grey{ 30,30,30,255};

	 InitWindow(windowWidth, windowHeight, "C++ Space Invaders");
	 ChangeDirectory("x64/Debug");
	 SetTargetFPS(60);

	 Game game;
	 while (WindowShouldClose() == false) {

		 game.HandleInput();
		 game.Update();
		 BeginDrawing();
		 ClearBackground(Grey);
		 game.Draw();	
		 EndDrawing();

	 }

	 CloseWindow();






}
