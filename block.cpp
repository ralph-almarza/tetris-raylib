#include "block.h"

Block::Block()
{
	cellSize = { 30 };
	rotationState = { 0 }; 
	colors = { GetCellColors() };
}

void Block::Draw()
{
	std::vector<Position> tiles = cells[rotationState];
	for (Position item : tiles)
	{
		DrawRectangle(item.column * cellSize + pixelOffset, item.row * cellSize + pixelOffset,
			cellSize - pixelOffset, cellSize - pixelOffset, colors[id]);
	}
}