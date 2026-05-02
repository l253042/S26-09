#include<raylib.h>
#include"game.hpp"


int main() {

	int windowWidth = 800;
	int windowHeight = 600;
	Color Grey{ 30,30,30,255};
	Color yellow = { 243,216,63,255 };

	 InitWindow(windowWidth , windowHeight, "C++ Space Invaders");
	 ChangeDirectory("x64/Debug");

	 Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	 Texture2D spaceshipimage = LoadTexture("Graphics/heart.png");

	 SetTargetFPS(60);

	 Game game;
	 while (WindowShouldClose() == false) {

		 game.HandleInput();
		 game.Update();
		 BeginDrawing();
		 ClearBackground(Grey);
		 DrawRectangleRoundedLinesEx({ 10,10,780,580 }, 0.18f, 20, 2, yellow);
		 DrawLineEx({ 25,545 }, { 775,545 }, 3, yellow);
		 if (game.run) {
			 DrawTextEx(font, "LEVEL 01", { 540,555 }, 34, 2, yellow);
		 }
		 else {
			 DrawTextEx(font, "GAME OVER", { 540,555 }, 34, 2, yellow);
		 }
		 float x = 50.0;
		 for (int i = 0; i < game.lives; i++) {
			 DrawTextureV(spaceshipimage, { x,546 }, WHITE);
			 x += 50;
		 }
		 game.Draw();	
		 EndDrawing();

	 }

	 CloseWindow();






}
