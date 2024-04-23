#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include "settings.h"

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
		
	std::map<int, std::vector<Position>> offsets; // rotation offsets for srs
	std::vector<Color> colors{};

private:
	int rowOffset{};
	int columnOffset{};

};