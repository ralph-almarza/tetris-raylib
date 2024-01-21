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

	Grid grid{};

private:
	std::vector<Block> blockBag{};
	Block currentBlock{};
};