#include "position.h"

Position::Position(int row, int column)
{
	// assigns value of parameter 'row' (2nd) to member variable 'row' (1st)
	this->row = row;		
	this->column = column;
}

// using this, the position of the block can now be represented as a single object