#pragma once
#include "grid.h"
#include "block-subclass.cpp"

class Game 
{
public:
	Game();
	std::vector<Block> RandomizeBag();
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
	void CheckCollisions();

	Grid grid{};

private:
	bool IsBlockInsideRight();
	bool IsBlockInsideLeft();
	void LockBlock();
	bool DoesBlockFit();

	std::vector<Block> blockBag{};
	Block currentBlock{};
	Block heldBlock{};
	bool isHoldEmpty{};
	Block nextBlock{};

	bool isHoldUsed;
};