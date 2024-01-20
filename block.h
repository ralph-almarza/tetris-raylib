#pragma once
#include <vector>
#include <map>
#include "position.h"

class Block
{
public:
	Block();
	
	int id;
	// a 'map' is used to denote the rotation state of the block
	std::map<int, std::vector<Position>> cells; 

private:
	int cellSize{}; 
	int rotationState{};

};