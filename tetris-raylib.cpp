#include <iostream>
#include <raylib.h>

#include "game.h"


int main()
{
	// Fixed FPS
	SetTargetFPS(60);

	// Create raylib game window
	InitWindow(1000, 1000, "Raylib Tetris");
	
	// Initialize game elements
	Game game{};
	game.grid.Print(); // Output grid in console

	// Create game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		game.Draw();
		ClearBackground(BLACK);
		EndDrawing();
	}

	return 0;
}
