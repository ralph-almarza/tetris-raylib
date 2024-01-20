#include <iostream>
#include <raylib.h>

int main()
{
	// Fixed FPS
	SetTargetFPS(60);

	// Create raylib game window
	InitWindow(1000, 1000, "Raylib Tetris");

	// Create game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		EndDrawing();
	}

	return 0;
}
