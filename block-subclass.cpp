#include "block.h"
#include "position.h"
// Do this later: update the positions of the blocks to be 1 unit up from the screen
// Only implement this after the blocks start moving 
class IBlock : public Block
{
public: 
	IBlock()
	{
		id = { 1 };
		cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
		cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
		cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
		cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
		Move(-1, 3); // Puts the block in the center of screen
	}
};

class OBlock : public Block
{
public:
	OBlock()
	{
		id = { 2 };
		cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		cells[1] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		cells[2] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		cells[3] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		Move(0, 4);
	}
};

class SBlock : public Block
{
public:
	SBlock()
	{
		id = { 3 };
		cells[0] = { Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) };
		cells[2] = { Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) };
		cells[3] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) };
		Move(0, 3);
	}
};

class ZBlock : public Block
{
public:
	ZBlock()
	{
		id = { 4 };
		cells[0] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) };
		cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) };
		Move(0, 3);
	}
};

class LBlock : public Block
{
public:
	LBlock()
	{
		id = { 5 };
		cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) };
		cells[3] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
		Move(0, 3);
	}
};

class JBlock : public Block
{
public:
	JBlock()
	{
		id = { 6 };
		cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) };
		cells[3] = { Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) };
		Move(0, 3);
	}
};

class TBlock : public Block
{
public:
	TBlock()
	{
		id = { 7 };
		cells[0] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) };
		Move(0, 3);
	}
};

