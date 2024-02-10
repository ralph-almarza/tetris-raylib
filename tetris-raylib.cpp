#include <iostream>
#include <raylib.h>
#include "game.h"

#include "constants.h"

int main()
{
	SetTargetFPS(60);
	InitWindow(windowWidth, windowHeight, "Raylib Tetris");
	
	Game game{};

	while (WindowShouldClose() == false)
	{
		game.HandleInput();

		BeginDrawing();
		game.Update();
		ClearBackground(BLACK);
		EndDrawing();
	}

	return 0;
}
