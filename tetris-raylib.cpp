#include <iostream>
#include <raylib.h>
#include "game.h"

// Pls fix I Block rotation, i tried
// Pls fix collisions (Blocks slides upwards when moving to the left)

int main()
{
	// Fixed FPS
	SetTargetFPS(60);

	// Create raylib game window
	InitWindow(1000, 1000, "Raylib Tetris");
	
	// Initialize game elements
	Game game{};
	game.grid.Print(); // Output grid in console

	double dasTimer = 0.0f;
	double arrTimer = 0.0f;

	// Create game loop
	while (WindowShouldClose() == false)
	{
		const float dasDelay = 0.30f; // Adjust as needed
        //const float arrDelay = 0.10f; // Adjust as needed

        // Input handling
        if (IsKeyDown(KEY_LEFT)) 
        {
			// Update timers
			dasTimer += GetFrameTime();
			arrTimer += GetFrameTime();

			if (dasTimer >= dasDelay) 
			{
				game.currentBlock.Move(0, -1);
				dasTimer = 0.0f;
			}
        }

		//game.HandleInput();

		BeginDrawing();
		game.Update();
		ClearBackground(BLACK);
		EndDrawing();
	}
	game.grid.Print(); // Output grid in console
	return 0;
}
