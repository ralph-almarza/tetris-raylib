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
	int GetRows();

	int grid[22][10]; // array of 22 rows and 10 columns


private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);

	int rows{};					// height of game grid 
	int columns{};				// width of game grid 
	std::vector<Color> colors{};	// 'Color' is a type available in raylib
};