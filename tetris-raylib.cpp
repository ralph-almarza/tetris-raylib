#include <iostream>
#include <raylib.h>

#include "game.h"

// Pls fix I Block rotation, i tried
// Pls fix collisions (Blocks slides upwards when moving to the left)


double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}


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
		game.HandleInput();
		//if (EventTriggered(0.2))
		//{
		//	game.MoveBlockDown();
		//}

		BeginDrawing();
		game.Draw();
		ClearBackground(BLACK);
		EndDrawing();
	}
	game.grid.Print(); // Output grid in console
	return 0;
}
