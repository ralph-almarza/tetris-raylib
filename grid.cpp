#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "colors.h"
#include "constants.h"

Grid::Grid() {
	Initialize();
	rows = { 22 };
	columns = { 10 };

	colors = GetCellColors();
}

void Grid::Initialize() {
	for (int row{ 0 }; row < rows; ++row) {
		for (int column{ 0 }; column < columns; ++column) {
			grid[row][column] = 0;
		}
	}
}

void Grid::Draw() {
	for (int row{ 0 }; row < rows; ++row) {
		for (int column{ 0 }; column < columns; ++column) {
			int cellValue = { grid[row][column] }; 
			DrawRectangle(((column * CELL_SIZE) + GRID_OFFSET), ((row * CELL_SIZE) + GRID_OFFSET),
				CELL_SIZE - GRID_OFFSET, CELL_SIZE - GRID_OFFSET, colors[static_cast<unsigned int>(cellValue)]);
		}
	}
}


// Collision and Boundary Checks
bool Grid::IsCellInside(int row, int column) {
	return (row >= 0 && row < rows) && (column >= 0 && column < columns);
}

bool Grid::IsCellEmpty(int row, int column) {
	return IsCellInside(row, column) && (grid[row][column] == 0);
}

bool Grid::IsRowFull(int row) {
	for (int column = 0; column < columns; column++) {
		if (grid[row][column] == 0)
			return false;
	}
	return true;
}

// Line Clears
int Grid::ClearFullRows() {
	int completed = 0;
	for (int row = rows - 1; row >= 0; row--) {
		if (IsRowFull(row)) {
			ClearRow(row);
			completed++;
		}
		else if (completed > 0) {
			MoveRowDown(row, completed);
		}
	}
	return completed;
}
void Grid::ClearRow(int row) {
	for (int column = 0; column < columns; column++) {
		grid[row][column] = 0;
	}
}
void Grid::MoveRowDown(int row, int completed) {
	for (int column = 0; column < columns; column++) {
		grid[row + completed][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
int Grid::GetRows() {
	return rows;
}


