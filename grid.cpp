#include "grid.h"
#include <iostream>
#include <raylib.h>

Grid::Grid() // Constructor
{
	numRows = { 20 };
	numColumns = { 10 };
	cellSize = { 30 };
	Print();

	colors = { GetCellColors() };
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

std::vector<Color> Grid::GetCellColors() // gets the color of the cell based on its value
{
	Color darkGrey	{ 26, 31, 40, 255 };	// Background Color
	Color cyan		{ 21, 204, 209, 255 };	// I-piece
	Color yellow	{ 237, 234, 4, 255 };	// O-piece
	Color green		{ 47, 230, 23, 255 };	// S-piece
	Color red		{ 232, 18, 18, 255 };	// Z-piece
	Color orange	{ 226, 116, 17, 255 };	// L-piece
	Color blue		{ 13, 64, 216, 255 };	// J-piece
	Color purple	{ 166, 0, 247, 255 };	// T-piece

	return { darkGrey, cyan, yellow, green, red, orange, blue, purple };
}