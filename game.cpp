#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG
#include "game.h"

#include <iostream>

#include <utility>

Game::Game()
{
	Reset();
}

void Game::Update()
{

	//BlockGravity();
	Draw();

	if (!DoesBlockFit())
		Reset();
}

void Game::Draw() // Draws the object in the game screen
{
	grid.Draw();
	DrawGhostBlock(currentBlock);
	currentBlock.Draw();
}
void Game::Reset()
{
	grid.Initialize();

	blockBag.clear();
	RandomizeBag();

	currentBlock = GetRandomBlock();
	currentBlock.ResetPosition();
	isHoldEmpty = true;
	isHoldUsed = false;
	lastUpdateTime = 0;

	arrTime = 0;
	arrDelay = 0.500;
	dasTime = 0;
	dasDelay = 0.5;
	
}

// Game Controls Methods
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
			(this->*actionFunction)();
	}
	else if (IsKeyReleased(key))
		arrTime = 0;
}

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


std::vector<std::vector<std::pair<int, int>>> Table() // this is now correct
{
	std::vector<std::vector<std::pair<int, int>>> offsetLSJZT
		= { {{0,0}, {0,0},  {0,0},   {0,0}, {0,0}},
			{{0,0}, {0,-1}, {-1,-1}, {2,0}, {2,-1}},
			{{0,0}, {0,0},  {0,0},   {0,0}, {0,0}},
			{{0,0}, {0,1},  {-1,1},  {2,0}, {2,1}}};

	std::vector<std::vector<std::pair<int, int>>> offsetI
		= { {{0,0}, {0,1},  {0,-2}, {0,1},  {0,-2}},
			{{0,1}, {0,0},  {0,0},  {1,0},  {-2,0}},
			{{1,1}, {1,-1}, {1,2},  {0,-1}, {0,2}},
			{{1,0}, {1,0},  {1,0},  {-1,0}, {2,0}}};

	std::vector < std::vector<std::pair<int, int >>> offsetO
		= {{ {0, 0},
			 {-1,0},
			 {-1,1},
			 {0, 1} }};

	return offsetI;
}

std::pair<int,int> ComputeResultantCoordinate(std::pair<int, int> initial, std::pair<int, int> final)
{
	std::pair<int, int> resultant = { final.first - initial.first, final.second - initial.second };

	return resultant;
}

std::pair<int, int> GetMoveCoordinate(int initRotate, int finalRotate)
{
	std::vector<std::vector<std::pair<int, int>>> table = Table();
	
	return ComputeResultantCoordinate(table[static_cast<size_t>(initRotate)][0], table[static_cast<size_t>(finalRotate)][0]);
}

// Rotation
// For the rotation states, modular arithmetic was used
void Game::RotateBlockClockwise()
{
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 1) % 4;

	std::pair<int, int> moveCoordinate = GetMoveCoordinate(initRotationState, currentBlock.rotationState);

	if (currentBlock.id == 1)
	{
		currentBlock.Move(moveCoordinate.first, moveCoordinate.second);
	}

}
void Game::RotateBlockCounterClockwise()
{
	currentBlock.rotationState = (currentBlock.rotationState + 3) % 4;
}
void Game::Rotate180()
{
	currentBlock.rotationState = (currentBlock.rotationState + 2) % 4;
}



// Holding, Locking and Dropping
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
void Game::HardDropBlock()
{
	DropBlock();
	LockBlock();
}
void Game::SoftDropBlock()
{
	DropBlock();
}
void Game::DropBlock()
{
	currentBlock.Move(BlockDropDistance(), 0);
}
void Game::LockBlock()
{
	for (Position item : currentBlock.GetCellPosition())
		grid.grid[item.row][item.column] = { currentBlock.id };

	currentBlock = GetRandomBlock();
	currentBlock.ResetPosition();
	isHoldUsed = { false };
	grid.ClearFullRows();
}


// Collision Detection
bool Game::DoesBlockFit()
{
	for (Position item : currentBlock.GetCellPosition())
	{
		if (!grid.IsCellEmpty(item.row, item.column))
			return false;
	}
	return true;
}



// Ghost Block Logic and Implementation
void Game::DrawGhostBlock(const Block& block)
{
	Block ghost = block;
	ghost.Move(BlockDropDistance(), 0);
	ghost.Draw();
}
int Game::TileDropDistance(const Position& block)
{
	int dropDistance{ 0 };

	while (grid.IsCellEmpty(block.row + dropDistance + 1, block.column))
		dropDistance++;

	return dropDistance;
}
int Game::BlockDropDistance()
{
	int minDistance = grid.GetRows();

	for (Position p : currentBlock.GetCellPosition())
		minDistance = std::min(minDistance, TileDropDistance(p));

	return minDistance;
}

// Block Queue Methods 
Block Game::GetRandomBlock()
{
	if (blockBag.empty())
		RandomizeBag();

	currentBlock = blockBag[0]; // Gets the first element of the random block
	blockBag.erase(blockBag.begin());

	return currentBlock;
}
void Game::RandomizeBag()
{
	blockBag = { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };

	// Seed the random number generator
	static std::random_device rd;
	static std::mt19937 rng(rd());

	// Shuffle the grouping of blocks
	std::shuffle(blockBag.begin(), blockBag.end(), rng);
}


// Gravity Feature
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