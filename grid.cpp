#include "grid.h"

#include <iostream>

Grid::Grid() // Constructor
{
	numRows = { 20 };
	numColumns = { 10 };
	cellSize = { 30 };
	Print();
}

void Grid::Print()
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