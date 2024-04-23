#include <iostream>
#include <raylib.h>
#include "game.h"

#include "settings.h"

int main()
{
	SetTargetFPS(90);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Tetris");
	
	Game game{};

	while (!WindowShouldClose())
	{
		game.HandleInput();

		BeginDrawing();
		game.Update();
		ClearBackground(BLACK);
		EndDrawing();
	}

	return 0;
}
