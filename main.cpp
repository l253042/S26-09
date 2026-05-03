#include<raylib.h>
#include"game.hpp"
#include<string>

std::string FormatWithLeadingZeros(int number, int width) {
	std::string numberText = std::to_string(number);
	int leadingZeros = width- numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {

	int windowWidth = 800;
	int windowHeight = 600;
	Color Grey{ 30,30,30,255};
	Color yellow = { 243,216,63,255 };

	 InitWindow(windowWidth , windowHeight, "C++ Space Invaders");
	 InitAudioDevice();
	 ChangeDirectory("x64/Debug");

	 Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	 Texture2D spaceshipimage = LoadTexture("Graphics/heart.png");

	 SetTargetFPS(60);

	 Game game;
	 while (WindowShouldClose() == false) {

		 UpdateMusicStream(game.music);
		 game.HandleInput();
		 game.Update();
		 BeginDrawing();
		 ClearBackground(Grey);
		 DrawRectangleRoundedLinesEx({ 10,10,780,580 }, 0.18f, 20, 2, yellow);
		 DrawLineEx({ 25,545 }, { 775,545 }, 3, yellow);
		 if (game.state == Game::STARTING) {
			 // Big title
			 Vector2 titleSize = MeasureTextEx(font, "SPACE INVADERS", 64, 2);
			 Vector2 subtitleSize = MeasureTextEx(font, "PRESS ENTER TO START", 34, 2);
			 DrawTextEx(font, "SPACE INVADERS", { (800 - titleSize.x) / 2, 220 }, 64, 2, yellow);
			 if ((int)(GetTime() * 2) % 2 == 0) {
				 DrawTextEx(font, "PRESS ENTER TO START", { (800 - subtitleSize.x) / 2, 320 }, 34, 2, yellow);
			 }
		 }
		 else if (game.state == Game::RUNNING) {
			 std::string levelText = "LEVEL " + FormatWithLeadingZeros(game.level, 2);
			 DrawTextEx(font, levelText.c_str(), { 540, 555 }, 34, 2, yellow);
		 }
		 else if (game.state == Game::LEVELUP) {
			 std::string levelText = "LEVEL " + std::to_string(game.level + 1) + " STARTING...";
			 std::string getreadyText = "GET READY!";
			 Vector2 levelSize = MeasureTextEx(font, levelText.c_str(), 64, 2);
			 Vector2 getreadySize = MeasureTextEx(font, getreadyText.c_str(), 64, 2);
			 DrawTextEx(font, levelText.c_str(), { (800 - levelSize.x) / 2, 260 }, 64, 2, yellow);
			 DrawTextEx(font, getreadyText.c_str(), { (800 - getreadySize.x) / 2, 300 }, 64, 2, yellow);
		 }
		 else if (game.state == Game::PAUSED) {
			 Vector2 pauseSize = MeasureTextEx(font, "PAUSED", 64, 2);
			 Vector2 resumeSize = MeasureTextEx(font, "PRESS P TO RESUME", 64, 2);
			 DrawTextEx(font, "PAUSED", { (800 - pauseSize.x) / 2, 240 }, 64, 2, yellow);
			 if ((int)(GetTime() * 2) % 2 == 0) {
				 DrawTextEx(font, "PRESS P TO RESUME", { (800 - resumeSize.x) / 2, 320 }, 64, 2, yellow);
			 }
		 }

		 else if (game.state == Game::GAMEOVER) {
			 Vector2 gameoverSize = MeasureTextEx(font, "GAME OVER", 64, 2);
			 Vector2 restartSize = MeasureTextEx(font, "PRESS ENTER TO RESTART", 64, 2);
			 DrawTextEx(font, "GAME OVER", { (800 - gameoverSize.x) / 2, 220 }, 64, 2, yellow);
			 if ((int)(GetTime() * 2) % 2 == 0) {
				 DrawTextEx(font, "PRESS ENTER TO RESTART", { (800 - restartSize.x) / 2, 310 }, 64, 2, yellow);
			 }
		 }
		 else if (game.state == Game::GAMECOMPLETED) {
			 Vector2 completedSize = MeasureTextEx(font, "YOU WIN!", 64, 2);
			 Vector2 scoreSize = MeasureTextEx(font, "CONGRATULATIONS!", 64, 2);
			 Vector2 restartSize = MeasureTextEx(font, "PRESS ENTER TO PLAY AGAIN", 64, 2);
			 DrawTextEx(font, "YOU WIN!", { (800 - completedSize.x) / 2, 180 }, 64, 2, yellow);
			 DrawTextEx(font, "CONGRATULATIONS!", { (800 - scoreSize.x) / 2, 260 }, 64, 2, yellow);
			 if ((int)(GetTime() * 2) % 2 == 0) {
				 DrawTextEx(font, "PRESS ENTER TO PLAY AGAIN", { (800 - restartSize.x) / 2, 340 }, 64, 2, yellow);
			 }
		 }

		 float x = 50.0;
		 for (int i = 0; i < game.lives; i++) {
			 DrawTextureV(spaceshipimage, { x,546 }, WHITE);
			 x += 50;
		 }
		 DrawTextEx(font, "SCORE", { 50,15 }, 34, 2, yellow);
		 std::string scoreText = FormatWithLeadingZeros(game.score, 5);
		 DrawTextEx(font, scoreText.c_str(), { 50,40 }, 34, 2, yellow);

		 DrawTextEx(font, "HIGH SCORE", { 570,15 }, 34, 2, yellow);
		 std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
		 DrawTextEx(font, highscoreText.c_str(), { 655,40 }, 34, 2, yellow);

		 game.Draw();	
		 EndDrawing();

	 }

	 CloseWindow();
	 CloseAudioDevice();



}
