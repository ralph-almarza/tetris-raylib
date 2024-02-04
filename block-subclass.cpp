#include "block.h"
#include "position.h"

// Updated I and O blocks

class IBlock : public Block
{
public: 
	IBlock()
	{
		id = { 1 };
		cells[0] = { Position(2, 1), Position(2, 2), Position(2, 3), Position(2, 4) };
		cells[1] = { Position(1, 2), Position(2, 2), Position(3, 2), Position(4, 2) };
		cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
		cells[3] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };

		offsets[0] = { Position(0,0), Position(0, 1), Position(0,-2), Position(0,1),  Position(0,-2) };
		offsets[1] = { Position(0,1), Position(0, 0), Position(0, 0), Position(1,0),  Position(-2,0) };
		offsets[2] = { Position(1,1), Position(1,-1), Position(1, 2), Position(0,-1), Position(0,2) };
		offsets[3] = { Position(1,0), Position(1, 0), Position(1, 0), Position(-1,0), Position(2,0) };
	}
};

class OBlock : public Block
{
public:
	OBlock()
	{
		id = { 2 };
		cells[0] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(1, 1), Position(1, 2), Position(2, 1), Position(2, 2) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(2, 0), Position(2, 1) };
		cells[3] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };

		offsets[0] = { Position(0, 0) };
		offsets[1] = { Position(-1,0) };
		offsets[2] = { Position(-1,1) };
		offsets[3] = { Position(0, 1) };
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

		offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0)  };
		offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
		offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0)  };
		offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1)  };
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

		offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
		offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1) };
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

		offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
		offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1) };
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

		offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
		offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1) };
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

		offsets[0] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[1] = { Position(0,0), Position(0,-1), Position(-1,-1), Position(2,0), Position(2,-1) };
		offsets[2] = { Position(0,0), Position(0,0),  Position(0, 0),  Position(0,0), Position(0,0) };
		offsets[3] = { Position(0,0), Position(0,1),  Position(-1,1),  Position(2,0), Position(2,1) };
	}
};

