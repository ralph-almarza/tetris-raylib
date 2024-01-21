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
		HoldBlock();
		break;
	}
}

void Game::MoveBlockRight()
{
	currentBlock.Move(0, 1);
}

void Game::MoveBlockLeft()
{
	currentBlock.Move(0, -1);
}

void Game::MoveBlockDown()
{
	currentBlock.Move(1, 0);
}

void Game::HoldBlock()
{
	if (!isBlockHeld)
	{
		// Remove the current block from screen

		// Put the current block into held block
		heldBlock = { currentBlock };

		// Set a flag indicating the block is held
		isBlockHeld = { true };

		// Get the next block in the bag to replace the held block
		currentBlock = { GetRandomBlock() };

		// Draw the new current block
		currentBlock.Draw();
	}
}