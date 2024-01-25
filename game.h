#pragma once
#include "grid.h"
#include "block-subclass.cpp"
#include "cmath"

class Game 
{
public:
	Game();
	void Update();
	void RandomizeBag();
	Block GetRandomBlock();
	void Draw();

	void HandleInput();
	void MoveBlockRight();
	void MoveBlockLeft();
	void MoveBlockDown();
	void RotateBlockClockwise();
	void RotateBlockCounterClockwise();
	void Rotate180();
	void HoldBlock();
	void HardDropBlock();
	void SoftDropBlock();

	Grid grid{};

	int BlockDropDistance();
	void DropBlock();
	void DrawGhostBlock(Block& currentBlock);

	bool EventTriggered(double interval);
	void BlockGravity();

	void CheckForKicks();

	Block currentBlock{};

private:
	bool IsBlockInsideRight();
	bool IsBlockInsideLeft();
	void LockBlock();
	bool DoesBlockFit();
	void Reset();

	std::vector<Block> blockBag{};
	//Block currentBlock{};
	Block heldBlock{};
	bool isHoldEmpty{};
	Block nextBlock{};

	bool isHoldUsed;

	int TileDropDistance(Position block);
	
	double lastUpdateTime{};


};