#include "colors.h"

const Color darkGrey	= { 26, 31, 40, 255 };		// Background Color
const Color cyan		= { 21, 204, 209, 255 };	// I-piece
const Color yellow		= { 237, 234, 4, 255 };		// O-piece
const Color green		= { 47, 230, 23, 255 };		// S-piece
const Color red			= { 232, 18, 18, 255 };		// Z-piece
const Color orange		= { 226, 116, 17, 255 };	// L-piece
const Color blue		= { 13, 64, 216, 255 };		// J-piece
const Color purple		= { 166, 0, 247, 255 };		// T-piece

std::vector<Color> GetCellColors() // gets the color of the cell based on its value
{
	return { darkGrey, cyan, yellow, green, red, orange, blue, purple };
}