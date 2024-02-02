#include "block.h"

Block::Block()
{
	cellSize = { 65 };
	pixelOffset = { 1 };
	colors = { GetCellColors() };

	rotationState = { 0 }; 
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

void Block::UndoMove(int row, int column)
{
	rowOffset -= row;
	columnOffset -= column;
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

void Block::ResetPosition() // Occurs when block is held
{
	rotationState = 0; // Position resets typically involves resetting rotation

	// Move the current block back to its initial position
	switch (id)
	{
	case 1:
		rowOffset = 0;
		columnOffset = 2;
		break;
	default:
		rowOffset = 1;
		columnOffset = 3;
		break;
	}

}