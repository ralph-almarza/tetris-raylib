#pragma once
#include "grid.h"
#include "block-subclass.cpp"
#include "cmath"

class Game 
{
public:
	Game();
	void Update();
	void Draw();
	void HandleInput();

	Grid grid{};

private:
	void DrawHoldBlock(const Block& block);
	void DrawNextBlock(const Block& block);


	// Game Controls Methods
	void HandleDelayedInput(int key, void (Game::* actionFunction)());
	void MoveBlock(int rowChange, int colChange);
	void MoveBlockRight();
	void MoveBlockLeft();
	void MoveBlockDown();
	void RotateBlockClockwise();
	void RotateBlockCounterClockwise();
	void Rotate180();
	void HoldBlock();
	void HardDropBlock();
	void SoftDropBlock();
	void LockBlock();
	void DropBlock();

	// Block Queue Methods
	void RandomizeBag();
	Block GetRandomBlock();

	// Ghost Block Methods
	void DrawGhostBlock(const Block& block);
	int TileDropDistance(const Position& block);
	int BlockDropDistance();

	// Gravity Methods
	void BlockGravity();
	bool EventTriggered(double interval);

	// Collision Methods
	bool DoesBlockFit();
	
	void CheckCollisions(int initRot, int finalRot);

	Position ComputeResultantCoordinate(Position initial, Position final);
	Position GetMoveCoordinate(int initRotate, int finalRotate);


	// Reset Game
	void Reset();

	// Variables
	
	Block currentBlock{};
	Block heldBlock{};
	std::vector<Block> blockBag{};

	bool isHoldEmpty{};
	bool isHoldUsed{};

	float arrTime{};
	float arrDelay{};
	float dasTime{};
	float dasDelay{};

	double lastUpdateTime{};
};