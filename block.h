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
	void UndoMove(int row, int column);
	std::vector<Position> GetCellPosition();
	void ResetPosition();

	int id{};
	int rotationState{};
	std::map<int, std::vector<Position>> cells; 
		// a 'map' is used to denote the rotation state of the block

	std::map<int, std::vector<Position>> offsets; // rotation offsets for srs

private:
	int cellSize{}; 
	std::vector<Color> colors{};
	int pixelOffset{};

	int rowOffset{};
	int columnOffset{};

};