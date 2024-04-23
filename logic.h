#pragma once
#include "grid.h"
#include "block-subclass.cpp"
#include "cmath"

class Logic {
public:
	Logic();
	void Update();

	

private:
	
	// Block Queue Methods
	void RandomizeBag();
	Block GetRandomBlock();

	// Ghost Block Methods
	
	int TileDropDistance(const Position& block);
	int BlockDropDistance();

	// Gravity Methods
	void BlockGravity();
	
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

};



