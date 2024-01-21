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
	void Move(int row, int column);
	std::vector<Position> GetCellPosition();
	void ResetPosition(int resetRow, int resetColumn);

	int id{};
	int rotationState{};
	std::map<int, std::vector<Position>> cells; 
		// a 'map' is used to denote the rotation state of the block

private:
	int cellSize{}; 
	std::vector<Color> colors{};
	int pixelOffset{ 1 };

	int rowOffset{};
	int columnOffset{};

};