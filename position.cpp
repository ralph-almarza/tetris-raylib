#include "position.h"

Position::Position(int row, int column) : row(row), column(column) { }

// using this, the position of the block can now be represented as a single object


/* to be implemented later if 
std::vector<std::vector<Position>> KickPositionTable =
{
	{ { 0, 1 },	{ 1, -1 },	{ 0, 2 },	{ 1,  2 } },
	{ { 0,-1 }, { -1, 1 },	{ 0,-2 },	{ -1,-2 } },
	{ { 0,-1 },	{ -1,-1 },	{ 0, 2 },	{ -1, 2 } },
	{ { 0, 1 },	{ 1,  1 },	{ 0,-2 },	{ 1, -2 } }
};*/