#include "game.h"
#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG

Game::Game()
{
	grid = { Grid() };
	blockBag = RandomizeBag();
	currentBlock = GetRandomBlock();
}

// Take careful attention in this function when implementing hold and also the queue of next pieces 
std::vector<Block> Game::RandomizeBag()
{
	blockBag = { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };

	// Seed the random number generator
	std::random_device rd;
	std::mt19937 rng(rd());

	// Shuffle the grouping of blocks
	std::shuffle(blockBag.begin(), blockBag.end(), rng);
	
	return blockBag;
}

Block Game::GetRandomBlock()
{
	if(blockBag.empty())
		blockBag = RandomizeBag();

	currentBlock = blockBag[0]; // Gets the first element of the random block
	blockBag.erase(blockBag.begin());

	return currentBlock;
}

void Game::Draw() // Draws the object in the game screen
{
	grid.Draw();
	currentBlock.Draw();
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	case KEY_H:
		if (!isBlockHeld)
			HoldBlock();
		else if (isBlockHeld)
			ReleaseHeldBlock();
		break;
	}
}

void Game::MoveBlockRight()
{
	currentBlock.Move(0, 1);
	if (IsBlockOutside())
		currentBlock.Move(0, -1);
}

void Game::MoveBlockLeft()
{
	currentBlock.Move(0, -1);
	if (IsBlockOutside())
		currentBlock.Move(0, 1);
}

void Game::MoveBlockDown()
{
	currentBlock.Move(1, 0);
	if (IsBlockOutside())
		currentBlock.Move(-1, 0);
}

void Game::RotateBlockClockwise()
{

}

void Game::RotateBlockCounterClockwise()
{

}

// Update this function in order for the block to move back to center after being held
void Game::HoldBlock()
{
	// Remove the current block from screen and
	// Put the current block into held block
	heldBlock = { currentBlock };

	// Set a flag indicating the block is held
	isBlockHeld = { true };

	// Get the next block in the bag to replace the held block
	currentBlock = { GetRandomBlock() };

	// Draw the new current block
	currentBlock.Draw();
}

void Game::ReleaseHeldBlock()
{
	// Remove the current block from the screen
	// Swap the held block with the current block
	std::swap(heldBlock, currentBlock);

	// Redraw the game with the new current block
	currentBlock.Draw();
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles) // Checks for each cell in the block if it's outside
	{
		if (grid.IsCellOutside(item.row, item.column))
			return true;
	}
	return false;
}
