#pragma once
#include <vector>
#include <raylib.h>

#include "position.h"

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();			
	void Draw();
	bool IsCellInside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();

	int grid[22][10]; // array of 22 rows and 10 columns


public:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);

	int numRows{};					// height of game grid 
	int numColumns{};				// width of game grid 
	int cellSize{};					// # of pixels denoting one cell in game grid 
	std::vector<Color> colors{};	// 'Color' is a type available in raylib
	int pixelOffset{ 1 };			// used for making the grid lines visible

};