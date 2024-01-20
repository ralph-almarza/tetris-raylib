#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
	Block();
	void Draw();
	
	int id{};
	// a 'map' is used to denote the rotation state of the block
	std::map<int, std::vector<Position>> cells; 

private:
	int cellSize{}; 
	int rotationState{};
	std::vector<Color> colors{};
	int pixelOffset{ 1 };

};