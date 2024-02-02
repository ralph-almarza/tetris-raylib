#include <iostream>
#include <raylib.h>
#include "game.h"

int main()
{
	SetTargetFPS(60);
	InitWindow(1500, 1500, "Raylib Tetris");
	
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
