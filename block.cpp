#include "block.h"

Block::Block()
{
	cellSize = { 30 };
	rotationState = { 0 }; 
	colors = { GetCellColors() };
}

void Block::Draw()
{
	std::vector<Position> tiles = GetCellPosition();
	for (Position item : tiles)
	{
		DrawRectangle(item.column * cellSize + pixelOffset, item.row * cellSize + pixelOffset,
			cellSize - pixelOffset, cellSize - pixelOffset, colors[id]);
	}
}

void Block::Move(int row, int column) // Used to change the block's position in the grid
{
	rowOffset += row;
	columnOffset += column;
}

std::vector<Position> Block::GetCellPosition() // Gets current position of block
{
	// Local orientation of the block (Rotation State)
	std::vector<Position> tiles = cells[rotationState];

	// Denotes how far the block moved from its initial position 
	std::vector<Position> movedTiles{};

	// New Position
	for (Position item : tiles)
	{
		Position newPosition = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPosition);
	}

	return movedTiles;
}

void Block::ResetPosition(int resetRow, int resetColumn)
{
	rowOffset = 0;
	columnOffset = 3;
	rotationState = 0;

	rowOffset = resetRow;
	columnOffset = resetColumn;
}