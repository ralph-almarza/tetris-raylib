#pragma once

class Grid
{
public:
	Grid();
	int grid[20][10] { 0 }; // array of 20 rows and 10 columns
	void Print();			// outputs the grid in console

private:
	int numRows{};	// height of game grid 
	int numColumns{};	// width of game grid 
	int cellSize{}; // # of pixels denoting one cell in game grid 
};