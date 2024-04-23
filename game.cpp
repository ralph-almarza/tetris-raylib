#include <random> // For generating random blocks
#include <algorithm> // For seeding the RNG
#include <iostream>
#include <utility>
#include "game.h"
#include "settings.h"


Game::Game() {
	Reset();
}

void Game::Update() {
	BlockGravity();
	Draw();

	if (!DoesBlockFit())
		Reset();
}

void Game::Draw() { // Draws the object in the game screen
	grid.Draw();
	DrawGhostBlock(currentBlock);
	currentBlock.Draw();
	DrawHoldBlock(heldBlock);
	DrawNextBlock(currentBlock); // errors when 7th block
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

void Game::DrawHoldBlock(const Block& block) {
	Block hold = block;

	hold.Move(0, 10);
	hold.Draw();
}
void Game::DrawNextBlock(const Block& block)
{
	Block ghost = block;

	ghost.Move(3, 10);
	ghost.Draw();
}
void Game::DrawGhostBlock(const Block& block)
{
	Block ghost = block;

	ghost.Move(BlockDropDistance(), 0);
	ghost.Draw();
}

// Game Controls Methods
void Game::HandleInput()
{
	HandleDelayedInput(MOVE_RIGHT, &Game::MoveBlockRight);
	HandleDelayedInput(MOVE_LEFT, &Game::MoveBlockLeft);

	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case MOVE_RIGHT:
		MoveBlockRight();
		break;
	case MOVE_LEFT:
		MoveBlockLeft();
		break;
	case ROTATE_CW:
		RotateBlockClockwise();
		break;
	case ROTATE_CCW:
		RotateBlockCounterClockwise();	
		break;
	case ROTATE_180:
		Rotate180();
		break;
	case HOLD:
		HoldBlock();
		break;
	case HARD_DROP:
		HardDropBlock();
		break;
	case SOFT_DROP:
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
		arrTime = 0;
}

// Movement
void Game::MoveBlock(int rowChange, int colChange) {
	currentBlock.Move(rowChange, colChange);
	if (!DoesBlockFit()) {
		currentBlock.Move(-rowChange, -colChange);
	}
}
void Game::MoveBlockRight() {
	MoveBlock(0, 1);
}
void Game::MoveBlockLeft() {
	MoveBlock(0, -1);
}
void Game::MoveBlockDown() {
	MoveBlock(1, 0);
}


Position Game::ComputeResultantCoordinate(Position initial, Position final) {
	return { final.row - initial.row, final.column - initial.column};
}
Position Game::GetMoveCoordinate(int initRot, int finalRot) {
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
void Game::CheckCollisions(int initRot, int finalRot) {
	GetMoveCoordinate(initRot, finalRot);
}

// Rotation
void Game::RotateBlockClockwise() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 1) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);

}
void Game::RotateBlockCounterClockwise() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 3) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);
}
void Game::Rotate180() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 2) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);
}



// Holding, Locking and Dropping
void Game::HoldBlock() {
	if (!isHoldUsed) {
		if (isHoldEmpty) {
			isHoldEmpty = { false };
			heldBlock = currentBlock;
			heldBlock.ResetPosition();

			// Remove the current block from the screen

			currentBlock = { GetRandomBlock() };
			currentBlock.ResetPosition();
		}
		else {
			std::swap(heldBlock, currentBlock);
			heldBlock.ResetPosition();
		}

		isHoldUsed = { true };
	}
}
void Game::HardDropBlock() {
	DropBlock();
	LockBlock();
}
void Game::SoftDropBlock() {
	DropBlock();
}
void Game::DropBlock()
{
	currentBlock.Move(BlockDropDistance(), 0);
}
void Game::LockBlock()
{
	for (Position cell : currentBlock.GetCellPosition())
		grid.grid[cell.row][cell.column] = { currentBlock.id };

	currentBlock = GetRandomBlock();
	currentBlock.ResetPosition();
	isHoldUsed = { false };
	grid.ClearFullRows();
}


// Collision Detection
bool Game::DoesBlockFit()
{
	for (Position cell : currentBlock.GetCellPosition())
	{
		if (!grid.IsCellEmpty(cell.row, cell.column))
			return false;
	}
	return true;
}


// Ghost Block Logic and Implementation
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

	currentBlock = blockBag[0];
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