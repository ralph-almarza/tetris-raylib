#pragma once
#include "grid.h"
#include "block-subclass.cpp"

class Game 
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();

	Grid grid{};

private:
	std::vector<Block> blockGrouping{};
	Block currentBlock{};
	Block nextBlock{};
};