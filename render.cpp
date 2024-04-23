#include "render.h"

void Render::Draw() { // Draws the object in the game screen
	grid.Draw();
	DrawGhostBlock(currentBlock);
	currentBlock.Draw();
	DrawHoldBlock(heldBlock);
	DrawNextBlock(currentBlock); // errors when 7th block
}

void Render::DrawHoldBlock(const Block& block) {
	Block hold = block;

	hold.Move(0, 10);
	hold.Draw();
}
void Render::DrawNextBlock(const Block& block)
{
	Block ghost = block;

	ghost.Move(3, 10);
	ghost.Draw();
}
void Render::DrawGhostBlock(const Block& block)
{
	Block ghost = block;

	ghost.Move(BlockDropDistance(), 0);
	ghost.Draw();
}
