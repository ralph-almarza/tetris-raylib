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
	for (const Position& tilePosition : tiles)
	{
		DrawRectangle(tilePosition.column * cellSize + pixelOffset, tilePosition.row * cellSize + pixelOffset,
			cellSize - pixelOffset, cellSize - pixelOffset, colors[static_cast<unsigned int>(id)]);
	}
}

void Block::Move(int row, int column) // Used to change the block's position in the grid
{
	rowOffset += row;
	columnOffset += column;
}

std::vector<Position> Block::GetCellPosition() // Gets current position of block
{
	// Denotes how far the block moved from its initial position 
	std::vector<Position> movedTiles{};

	// New Position
	for (const Position& tilePosition : cells[rotationState])
	{
		Position newPosition = Position(tilePosition.row + rowOffset, tilePosition.column + columnOffset);
		movedTiles.push_back(newPosition);
	}

	return movedTiles;
}

void Block::ResetPosition()
{
	rotationState = 0; // Position resets typically involves resetting rotation

	// Move the current block back to its initial position
	switch (id)
	{
	case 1:
		rowOffset = -1;
		columnOffset = 3;
		break;
	case 2:
		rowOffset = 0;
		columnOffset = 4;
		break;
	default:
		rowOffset = 0;
		columnOffset = 3;
		break;
	}

}