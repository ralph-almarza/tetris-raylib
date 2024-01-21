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
	void ReleaseHeldBlock();

	Grid grid{};

private:
	bool IsBlockOutsideRight();
	bool IsBlockOutsideLeft();
	bool IsBlockOutsideDown();
	void CollisionsCheck();

	std::vector<Block> blockBag{};
	Block currentBlock{};
	Block heldBlock{};
	bool isBlockHeld{ false };
	

};