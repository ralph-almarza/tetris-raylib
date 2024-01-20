#include "colors.h"

const Color darkGrey	= { 45, 48, 71, 200 };		// Background Color
const Color cyan		= { 126, 241, 228, 255 };	// I-piece
const Color yellow		= { 255, 210, 63, 255 };	// O-piece
const Color green		= { 0, 168, 120, 255 };		// S-piece
const Color red			= { 238, 66, 102, 255 };	// Z-piece
const Color orange		= { 226, 116, 17, 255 };	// L-piece
const Color blue		= { 77, 157, 224, 255 };	// J-piece
const Color purple		= { 119, 104, 174, 255 };	// T-piece

std::vector<Color> GetCellColors() // gets the color of the cell based on its value
{
	return { darkGrey, cyan, yellow, green, red, orange, blue, purple };
}