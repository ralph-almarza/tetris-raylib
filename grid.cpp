#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "colors.h"

Grid::Grid() // Constructor
{
	Initialize();
	numRows = { 22 };
	numColumns = { 10 };
	cellSize = { 30 };

	colors = GetCellColors();
}

void Grid::Initialize()
{
	for (int row{ 0 }; row < numRows; ++row)
	{
		for (int column{ 0 }; column < numColumns; ++column)
		{
			grid[row][column] = 0;
		}
	}
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

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}


bool Grid::IsRowFull(int row)
{
	for (int column = 0; column < numColumns; column++)
	{
		if (grid[row][column] == 0)
			return false;
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int column = 0; column < numColumns; column++)
	{
		grid[row][column] == 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numColumns; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}

