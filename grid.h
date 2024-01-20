#pragma once

class Grid
{
public:
	Grid();
	int grid[20][10] { 0 }; // array of 20 rows and 10 columns

private:
	int numRows{}; // height of game grid 
	int numCols{}; // width of game grid 
	int cellSize{}; // # of pixels denoting one cell in game grid 
};