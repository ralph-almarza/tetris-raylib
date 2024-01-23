#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "colors.h"

Grid::Grid() // Constructor
{
	numRows = { 22 };
	numColumns = { 10 };
	cellSize = { 30 };

	colors = GetCellColors();
}

void Grid::Print() // outputs the grid in console
{
	for (int row{ 0 }; row < numRows; ++row)
	{
		for (int column{ 0 }; column < numColumns; ++column)
		{
			std::cout << grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::Draw() // draws the grid in raylib game window
{
	for (int row{ 0 }; row < numRows; ++row)
	{
		for (int column{ 0 }; column < numColumns; ++column)
		{
			int cellValue = { grid[row][column] }; // cell changes color based on cellValue, default value is 0
			DrawRectangle(column * cellSize + pixelOffset, row * cellSize + pixelOffset,
				cellSize - pixelOffset, cellSize - pixelOffset, colors[cellValue]);
		}
	}
}

bool Grid::IsCellInside(int row, int column)
{
	return (row >= 0 && row < numRows) && (column >= 0 && column < numColumns);
}

bool Grid::IsCellEmpty(int row, int column)
{
	return IsCellInside(row, column) && (grid[row][column] == 0);
}
