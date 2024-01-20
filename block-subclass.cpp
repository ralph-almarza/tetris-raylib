#include "block.h"
#include "position.h"

class IBlock : public Block
{
public: 
	IBlock()
	{
		id = { 1 };
		cells[0] = { Position(0, 0), Position(0, 1), Position(0, 2), Position(0, 3) };
		cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
		cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
		cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
	}
};