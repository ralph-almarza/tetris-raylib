#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG
#include "game.h"

#include <iostream>

Game::Game()
{
	grid.Initialize();
	RandomizeBag();
	currentBlock = GetRandomBlock();
	isHoldEmpty = true;
	isHoldUsed = false;
	lastUpdateTime = 0;

	arrTime = 0;
	arrDelay = 0.500;
	dasTime = 0;
	dasDelay = 0.5;
}

void Game::Update()
{
	//BlockGravity();
	Draw();

	if (!DoesBlockFit())
	{
		Reset();
	}
}

void Game::BlockGravity()
{
	if (EventTriggered(0.2))
	{
		MoveBlockDown();
	}
}

bool Game::EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}


void Game::Draw() // Draws the object in the game screen
{
	grid.Draw();
	DrawGhostBlock(currentBlock);
	currentBlock.Draw();
}

void Game::HandleInput()
{
	HandleDelayedInput(KEY_LEFT, &Game::MoveBlockLeft);
	HandleDelayedInput(KEY_RIGHT, &Game::MoveBlockRight);

	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_LEFT:
		MoveBlockLeft();
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
		HardDropBlock();
		break;
	case KEY_N:
		SoftDropBlock();
		break;
	}
}

void Game::HandleDelayedInput(int key, void (Game::*actionFunction)())
{
	if (IsKeyDown(key))
	{
		arrTime += GetFrameTime();
		dasTime += GetFrameTime();

		if (arrTime >= arrDelay && dasTime >= dasDelay)
		{
			(this->*actionFunction)();
		}
	}
	else if (IsKeyReleased(key))
	{
		arrTime = 0;
	}
}


// Block Queue Methods 
void Game::RandomizeBag()
{
	blockBag = { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };

	// Seed the random number generator
	static std::random_device rd;
	static std::mt19937 rng(rd());

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
void Game::MoveBlock(int rowChange, int colChange)
{
	currentBlock.Move(rowChange, colChange);
	if (!DoesBlockFit())
		currentBlock.Move(-rowChange, -colChange);
}
void Game::MoveBlockRight()
{
	MoveBlock(0, 1);
}
void Game::MoveBlockLeft()
{
	MoveBlock(0, -1);
}
void Game::MoveBlockDown()
{
	MoveBlock(1, 0);
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
	CheckForKicks();
}
void Game::RotateBlockCounterClockwise()
{
	currentBlock.rotationState = (currentBlock.rotationState + 3) % 4;

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
		currentBlock.ResetPosition();

		if (isHoldEmpty)
		{
			// Remove the current block from the screen
			heldBlock = { currentBlock };

			// Get the next block in the bag to replace the held block
			currentBlock = { GetRandomBlock() };

			isHoldEmpty = { false };
			isHoldUsed = { true };

		}
		else if (!isHoldEmpty)
		{
			// Swap the held block with the current block
			std::swap(heldBlock, currentBlock);

			isHoldUsed = { true };
		}
	}
}
void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
		grid.grid[item.row][item.column] = currentBlock.id;

	currentBlock = GetRandomBlock();
	isHoldUsed = false;
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

bool Game::DoesBlockFit()
{
	for (Position item : currentBlock.GetCellPosition())
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

int Game::TileDropDistance(const Position& block)
{
	int drop{ 0 };

	while (grid.IsCellEmpty(block.row + drop + 1, block.column))
		drop++;

	return drop;
}

int Game::BlockDropDistance()
{
	int minDistance = grid.GetRows();

	for (Position p : currentBlock.GetCellPosition())
		minDistance = std::min(minDistance, TileDropDistance(p));

	return minDistance;
}

void Game::DropBlock()
{
	currentBlock.Move(BlockDropDistance(), 0);
}

void Game::DrawGhostBlock(const Block& block)
{
	Block ghost = block;
	ghost.Move(BlockDropDistance(), 0);
	ghost.Draw();
}

void Game::HardDropBlock()
{
	DropBlock();
	LockBlock();
}
void Game::SoftDropBlock()
{
	DropBlock();
}

void Game::CheckForKicks()
{
	const int kickPositionAttempts = 5;

	if (currentBlock.rotationState == 2)
	{
		for (int i = 0; i < kickPositionAttempts; i++)
		{
			if (DoesBlockFit())
			{
				break;
			}
			if (!DoesBlockFit())
			{
				switch (i)
				{
				case 0:
					currentBlock.Move(0, 1);
					break;
				case 1:
					currentBlock.UndoMove(0, 1); // undo movement
					currentBlock.Move(1, 1); // test new position
					break;
				case 2:
					currentBlock.UndoMove(1, 1);
					currentBlock.Move(-2, 0);
					break;
				case 3:
					currentBlock.UndoMove(-2, 0); 
					currentBlock.Move(-2, 1);
					break;
				case 4:
					currentBlock.rotationState--;
					std::cout << "rotation failed." << std::endl;
				}
			}
		}
	}
}

