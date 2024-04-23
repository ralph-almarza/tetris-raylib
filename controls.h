#pragma once
#include "position.h"

class Controls
{
public:
	void HandleInput();
	// Game Controls Methods
	void HandleDelayedInput(int key, void (Game::* actionFunction)());
	void MoveBlock(int rowChange, int colChange);
	void MoveBlockRight();
	void MoveBlockLeft();
	void MoveBlockDown();
	void RotateBlockClockwise();
	void RotateBlockCounterClockwise();
	void Rotate180();
	void HoldBlock();
	void HardDropBlock();
	void SoftDropBlock();
	void LockBlock();
	void DropBlock();
	Game game{};
};