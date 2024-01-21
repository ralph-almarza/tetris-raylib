#include "game.h"
#include <random> // For generating random blocks

Game::Game()
{
	grid = { Grid() };
	blockGrouping = GetAllBlocks();
}

// Take careful attention in this function when implementing hold and also the queue of next pieces 
Block Game::GetRandomBlock()
{
	if (blockGrouping.empty())
	{
		blockGrouping = GetAllBlocks();
	}
	int randomIndex = rand() % blockGrouping.size();
	Block block = blockGrouping[randomIndex];
	blockGrouping.erase(blockGrouping.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), OBlock(), SBlock(), ZBlock(), LBlock(), JBlock(), TBlock() };
}