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
	void HoldBlock();

	Grid grid{};

private:
	std::vector<Block> blockBag{};
	Block currentBlock{};
	Block heldBlock{};

	bool isBlockHeld{ false };
};