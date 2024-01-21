#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid();
	void Print();			
	void Draw();
	bool IsCellOutside(int row, int column);

	int grid[20][10] { 0 }; // array of 20 rows and 10 columns

private:
	int numRows{};					// height of game grid 
	int numColumns{};				// width of game grid 
	int cellSize{};					// # of pixels denoting one cell in game grid 
	std::vector<Color> colors{};	// 'Color' is a type available in raylib
	int pixelOffset{ 1 };			// used for making the grid lines visible
};