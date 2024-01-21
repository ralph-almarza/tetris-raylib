#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "block-subclass.cpp"


int main()
{
	// Fixed FPS
	SetTargetFPS(60);

	// Create raylib game window
	InitWindow(1000, 1000, "Raylib Tetris");
	
	Grid grid{};

	// Test if block is displayed correctly in screen
	IBlock block{}; 

	// Test if block changes position in screen
	block.Move(4, 3);

	// Create game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		grid.Draw();
		block.Draw();
		ClearBackground(BLACK);
		EndDrawing();
	}

	return 0;
}
