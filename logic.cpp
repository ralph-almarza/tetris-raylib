#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG
#include <iostream>
#include <utility>
#include "logic.h"


Logic::Logic() {
	Reset();
}

void Logic::Update() {
	BlockGravity();
	Render::Draw();

	if (!DoesBlockFit())
		Reset();
}


void Logic::Reset()
{

	blockBag.clear();
	RandomizeBag();

	currentBlock = GetRandomBlock();
	currentBlock.ResetPosition();

	isHoldEmpty = true;
	isHoldUsed = false;
	
}





Position Logic::ComputeResultantCoordinate(Position initial, Position final) {
	return { final.row - initial.row, final.column - initial.column};
}
Position Logic::GetMoveCoordinate(int initRot, int finalRot) {
	Position coordinate{ 0,0 };

	for (unsigned int i = 0; i < currentBlock.offsets[initRot].size(); ++i)
	{
		coordinate = ComputeResultantCoordinate(currentBlock.offsets[initRot][i], currentBlock.offsets[finalRot][i]);
		currentBlock.Move(coordinate.row, coordinate.column);

		if (DoesBlockFit())
		{
			std::cout << "break!";
			break;
		}
		else if (!DoesBlockFit())
		{
			currentBlock.UndoMove(coordinate.row, coordinate.column);
			std::cout << "test! " << i << " ";
		}
	}

	return coordinate;
};
void Logic::CheckCollisions(int initRot, int finalRot) {
	GetMoveCoordinate(initRot, finalRot);
}







// Collision Detection
bool Logic::DoesBlockFit()
{
	for (Position cell : currentBlock.GetCellPosition())
	{
		if (!grid.IsCellEmpty(cell.row, cell.column))
			return false;
	}
	return true;
}


// Ghost Block Logic and Implementation
int Logic::TileDropDistance(const Position& block)
{
	int dropDistance{ 0 };

	while (grid.IsCellEmpty(block.row + dropDistance + 1, block.column))
		dropDistance++;

	return dropDistance;
}
int Logic::BlockDropDistance()
{
	int minDistance = grid.GetRows();

	for (Position p : currentBlock.GetCellPosition())
		minDistance = std::min(minDistance, TileDropDistance(p));

	return minDistance;
}

// Block Queue Methods 
Block Logic::GetRandomBlock()
{
	if (blockBag.empty())
		RandomizeBag();

	currentBlock = blockBag[0];
	blockBag.erase(blockBag.begin());

	return currentBlock;
}
void Logic::RandomizeBag()
{
	blockBag = { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };

	// Seed the random number generator
	static std::random_device rd;
	static std::mt19937 rng(rd());

	// Shuffle the grouping of blocks
	std::shuffle(blockBag.begin(), blockBag.end(), rng);
}


// Gravity Feature
void Logic::BlockGravity()
{
	if (EventTriggered(0.2))
	{
		MoveBlockDown();
	}
}
