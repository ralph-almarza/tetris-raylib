#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG

#include "game.h"

Game::Game()
{
	grid.Initialize();
	RandomizeBag();
	currentBlock = GetRandomBlock();
	isHoldEmpty = true;
	isHoldUsed = false;
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
		DropBlock();
		LockBlock();
		break;
	}
}


// Block Queue Methods 
void Game::RandomizeBag()
{
	blockBag = { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };

	// Seed the random number generator
	std::random_device rd;
	std::mt19937 rng(rd());

	// Shuffle the grouping of blocks
	std::shuffle(blockBag.begin(), blockBag.end(), rng);
}
Block Game::GetRandomBlock()
{
	if (blockBag.empty())
		RandomizeBag();

	currentBlock = blockBag[0]; // Gets the first element of the random block
	blockBag.erase(blockBag.begin());

	return currentBlock;
}


// Game Controls Methods
	// Movement
void Game::MoveBlockRight()
{
	currentBlock.Move(0, 1);
	if (!DoesBlockFit())
		currentBlock.Move(0, -1);
}
void Game::MoveBlockLeft()
{
	currentBlock.Move(0, -1);
	if (!DoesBlockFit())
		currentBlock.Move(0, 1);
}
void Game::MoveBlockDown()
{
	currentBlock.Move(1, 0);
	if (!DoesBlockFit())
		currentBlock.Move(-1, 0);
}
	// Rotation
	// For the rotation states, modular arithmetic was used
void Game::RotateBlockClockwise()
{
	currentBlock.rotationState = (currentBlock.rotationState + 1) % 4;
	if (!IsBlockInsideLeft())
		currentBlock.Move(0, -2);
	if (!IsBlockInsideRight())
		currentBlock.Move(0, 2);
	if (!DoesBlockFit())
		currentBlock.Move(-2, 0);
}
void Game::RotateBlockCounterClockwise()
{
	if (currentBlock.rotationState == 0)
		currentBlock.rotationState = 3;
	else
		currentBlock.rotationState--;

	if (!IsBlockInsideLeft())
		currentBlock.Move(0, -2);
	if (!IsBlockInsideRight())
		currentBlock.Move(0, 2);
	if (!DoesBlockFit())
		currentBlock.Move(-2, 0);

}
void Game::Rotate180()
{
	currentBlock.rotationState = (currentBlock.rotationState + 2) % 4;
	
	if (!IsBlockInsideLeft())
		currentBlock.Move(0, 2);
	if (!IsBlockInsideRight())
		currentBlock.Move(0, -2);
	if (!DoesBlockFit())
		currentBlock.Move(-1, 0);
}
	// Holding and Locking 
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
void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
		grid.grid[item.row][item.column] = currentBlock.id;
	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
	isHoldUsed = { false };
	grid.ClearFullRows();
}


// Collision Detection
bool Game::IsBlockInsideRight()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (!(grid.IsCellInside(item.row, item.column)) && item.column < 9)
			return false;
	}
	return true;
}
bool Game::IsBlockInsideLeft()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (!(grid.IsCellInside(item.row, item.column)) && item.column > 0)
			return false;
	}
	return true;
}

void Game::CheckCollisions()
{
}

bool Game::DoesBlockFit()
{
	std::vector<Position>tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (!grid.IsCellEmpty(item.row, item.column))
			return false;
	}
	return true;
}

void Game::Reset()
{
	grid.Initialize();

	blockBag.clear();
	RandomizeBag();

	currentBlock = GetRandomBlock();
	isHoldEmpty = true;
	isHoldUsed = false;
}

int Game::TileDropDistance(Position block)
{
	int drop{ 0 };

	while (grid.IsCellEmpty(block.row + drop + 1, block.column))
	{
		drop++;
	}

	return drop;
}

int Game::BlockDropDistance()
{
	int drop = grid.numRows;

	for (Position block : currentBlock.GetCellPosition())
	{
		drop = fmin(static_cast<long double>(drop), static_cast<long double>(TileDropDistance(block)));
	}
	return drop;
}

void Game::DropBlock()
{
	currentBlock.Move(BlockDropDistance(), 0);
}