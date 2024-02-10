#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "colors.h"
#include "constants.h"

Grid::Grid()
{
	Initialize();
	numRows = { 22 };
	numColumns = { 10 };

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
			int cellValue = { grid[row][column] }; 
			DrawRectangle(((column * cellSize) + gridPixelOffset), 
				((row * cellSize) + gridPixelOffset),
				cellSize - gridPixelOffset, cellSize - gridPixelOffset, 
				colors[static_cast<unsigned int>(cellValue)]);
		}
	}
}


// Used for Collision and Boundary Checks
bool Grid::IsCellInside(int row, int column)
{
	return (row >= 0 && row < numRows) && (column >= 0 && column < numColumns);
}
bool Grid::IsCellEmpty(int row, int column)
{
	return IsCellInside(row, column) && (grid[row][column] == 0);
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

// Line Clears
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
void Grid::ClearRow(int row)
{
	for (int column = 0; column < numColumns; column++)
	{
		grid[row][column] = 0;
	}
}
void Grid::MoveRowDown(int row, int completed)
{
	for (int column = 0; column < numColumns; column++)
	{
		grid[row + completed][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
int Grid::GetRows()
{
	return numRows;
}


