#include <iostream>
#include <raylib.h>

#include "grid.h"

Grid grid{};

int main()
{
	// Fixed FPS
	SetTargetFPS(60);

	// Create raylib game window
	InitWindow(1000, 1000, "Raylib Tetris");
	
	// Check if colors work well
	grid.grid[0][0] = 1;
	grid.grid[0][1] = 2;
	grid.grid[0][2] = 3;
	grid.grid[0][3] = 4;

	// Create game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		grid.Draw();
		ClearBackground(WHITE);
		EndDrawing();
	}

	return 0;
}
