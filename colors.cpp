#include "colors.h"

constexpr Color darkGrey	= { 45, 48, 71, 200 };		// Background Color
constexpr Color cyan		= { 126, 241, 228, 255 };	// I-piece
constexpr Color yellow		= { 255, 210, 63, 255 };	// O-piece
constexpr Color green		= { 0, 168, 120, 255 };		// S-piece
constexpr Color red			= { 238, 66, 102, 255 };	// Z-piece
constexpr Color orange		= { 226, 116, 17, 255 };	// L-piece
constexpr Color blue		= { 77, 157, 224, 255 };	// J-piece
constexpr Color purple		= { 119, 104, 174, 255 };	// T-piece

std::vector<Color> GetCellColors() noexcept // gets the color of the cell based on its value
{
	return { darkGrey, cyan, yellow, green, red, orange, blue, purple };
}