#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG

#include "game.h"

Game::Game()
{
	grid = { Grid() };
	blockBag = RandomizeBag();
	currentBlock = GetRandomBlock();
	isHoldEmpty = { true };
	isHoldUsed = { false };
}

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
	case KEY_PERIOD:
		RotateBlockClockwise();
		break;
	case KEY_COMMA:
		RotateBlockCounterClockwise();
		break;
	case KEY_SLASH:
		Rotate180();
		break;
	case KEY_H:
		HoldBlock();
		break;
	case KEY_SPACE:
		LockBlock();
		break;
	}
}

void Game::MoveBlockRight()
{
	currentBlock.Move(0, 1);
	if (IsBlockOutsideRight())
		currentBlock.Move(0, -1);
	CheckCollisions();
}
void Game::MoveBlockLeft()
{
	currentBlock.Move(0, -1);
	if (IsBlockOutsideLeft())
		currentBlock.Move(0, 1);
	CheckCollisions();
}
void Game::MoveBlockDown()
{
	currentBlock.Move(1, 0);
	if (IsBlockOutsideLeft())
		currentBlock.Move(-1, 0);
	CheckCollisions();
}

// For the rotation states, modular arithmetic was used
void Game::RotateBlockClockwise()
{
	currentBlock.rotationState = (currentBlock.rotationState + 1) % 4;
	CheckCollisions();
}
void Game::RotateBlockCounterClockwise()
{
	currentBlock.rotationState = (currentBlock.rotationState - 1 + 4) % 4;
	CheckCollisions();
}
void Game::Rotate180()
{
	currentBlock.rotationState = (currentBlock.rotationState + 2) % 4;
	CheckCollisions();
}

void Game::HoldBlock()
{
	if (!isHoldUsed)
	{
		// Move the current block back to its initial position
		switch (currentBlock.id)
		{
		case 1:
			currentBlock.ResetPosition(-1, 3);
			break;
		case 2:
			currentBlock.ResetPosition(0, 4);
			break;
		default:
			currentBlock.ResetPosition(0, 3);
			break;
		}

		if (isHoldEmpty)
		{
			// Remove the current block from the screen
			heldBlock = { currentBlock };

			// Get the next block in the bag to replace the held block
			currentBlock = { GetRandomBlock() };

			// Redraw the game with the new current block
			currentBlock.Draw();

			// Set a flag indicating the block is held
			isHoldEmpty = { false };
			isHoldUsed = { true };

		}
		else if (!isHoldEmpty)
		{
			// Swap the held block with the current block
			std::swap(heldBlock, currentBlock);

			// Redraw the game with the new current block
			currentBlock.Draw();
			isHoldUsed = { true };
		}
	}
}

bool Game::IsBlockOutsideRight()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles) // Checks for each cell in the block if it's outside
	{
		if (grid.IsCellOutside(item.row, item.column) && item.column > 9)
			return true;
	}
	return false;

}

bool Game::IsBlockOutsideLeft()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column) && item.column < 0)
			return true;
	}
	return false;

}

bool Game::IsBlockOutsideDown()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
			return true;
	}
	return false;
}

void Game::CheckCollisions()
{
	if (IsBlockOutsideRight() || !DoesBlockFit())
		currentBlock.Move(0, -1);

	if (IsBlockOutsideLeft() || !DoesBlockFit())
		currentBlock.Move(0, 1);

	if (IsBlockOutsideDown())
		currentBlock.Move(-1, 0);

	if (!DoesBlockFit())
		currentBlock.Move(-1, 0);
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
		grid.grid[item.row][item.column] = currentBlock.id;
	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
	isHoldUsed = { false };
}

bool Game::DoesBlockFit()
{
	std::vector<Position>tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.column) == false)
			return false;
	}
	return true;
}
