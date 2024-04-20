#include "block.h"

Block::Block()
{
	colors = { GetCellColors() };

	rotationState = { 0 }; 

	offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
	offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
	offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
	offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1) };
}

void Block::Draw() {
	std::vector<Position> tiles = GetCellPosition();
	for (const Position& tilePosition : tiles) {
		DrawRectangle(tilePosition.column * CELL_SIZE + GRID_OFFSET, tilePosition.row * CELL_SIZE + GRID_OFFSET,
			CELL_SIZE - GRID_OFFSET, CELL_SIZE - GRID_OFFSET, colors[static_cast<unsigned int>(id)]);
	}

}

void Block::Move(int row, int column)
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
	rotationState = 0; 
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