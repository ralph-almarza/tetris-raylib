#include "controls.h"
#include "configs.h"
#include <raylib.h>

// Game Controls Methods
void Controls::HandleInput()
{
	HandleDelayedInput(MOVE_RIGHT, &Controls::MoveBlockRight);
	HandleDelayedInput(MOVE_LEFT, &Controls::MoveBlockLeft);

	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case MOVE_RIGHT:
		MoveBlockRight();
		break;
	case MOVE_LEFT:
		MoveBlockLeft();
		break;
	case ROTATE_CW:
		RotateBlockClockwise();
		break;
	case ROTATE_CCW:
		RotateBlockCounterClockwise();
		break;
	case ROTATE_180:
		Rotate180();
		break;
	case HOLD:
		HoldBlock();
		break;
	case HARD_DROP:
		HardDropBlock();
		break;
	case SOFT_DROP:
		SoftDropBlock();
		break;
	}
}
void Controls::HandleDelayedInput(int key, void (Controls::* actionFunction)())
{
	if (IsKeyDown(key))
	{
		arrTime += GetFrameTime();
		dasTime += GetFrameTime();

		if (arrTime >= arrDelay && dasTime >= dasDelay)
		{
			(this->*actionFunction)();
		}
	}
	else if (IsKeyReleased(key))
		arrTime = 0;
}

// Movement
void Controls::MoveBlock(int rowChange, int colChange) {
	currentBlock.Move(rowChange, colChange);
	if (!DoesBlockFit()) {
		currentBlock.Move(-rowChange, -colChange);
	}
}
void Controls::MoveBlockRight() {
	MoveBlock(0, 1);
}
void Controls::MoveBlockLeft() {
	MoveBlock(0, -1);
}
void Controls::MoveBlockDown() {
	MoveBlock(1, 0);
}


Position Controls::ComputeResultantCoordinate(Position initial, Position final) {
	return { final.row - initial.row, final.column - initial.column };
}
Position Controls::GetMoveCoordinate(int initRot, int finalRot) {
	Position coordinate{ 0,0 };

	for (unsigned int i = 0; i < currentBlock.offsets[initRot].size(); ++i)
	{
		coordinate = ComputeResultantCoordinate(currentBlock.offsets[initRot][i], currentBlock.offsets[finalRot][i]);
		currentBlock.Move(coordinate.row, coordinate.column);

		if (DoesBlockFit())
		{
			std::cout << "break!";
			break;
		}
		else if (!DoesBlockFit())
		{
			currentBlock.UndoMove(coordinate.row, coordinate.column);
			std::cout << "test! " << i << " ";
		}
	}

	return coordinate;
};
void Controls::CheckCollisions(int initRot, int finalRot) {
	GetMoveCoordinate(initRot, finalRot);
}

// Rotation
void Controls::RotateBlockClockwise() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 1) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);

}
void Controls::RotateBlockCounterClockwise() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 3) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);
}
void Controls::Rotate180() {
	int initRotationState = currentBlock.rotationState;
	currentBlock.rotationState = (currentBlock.rotationState + 2) % 4;

	CheckCollisions(initRotationState, currentBlock.rotationState);
}



// Holding, Locking and Dropping
void Controls::HoldBlock() {
	if (!isHoldUsed) {
		if (isHoldEmpty) {
			isHoldEmpty = { false };
			heldBlock = currentBlock;
			heldBlock.ResetPosition();

			// Remove the current block from the screen

			currentBlock = { GetRandomBlock() };
			currentBlock.ResetPosition();
		}
		else {
			std::swap(heldBlock, currentBlock);
			heldBlock.ResetPosition();
		}

		isHoldUsed = { true };
	}
}
void Controls::HardDropBlock() {
	DropBlock();
	LockBlock();
}
void Controls::SoftDropBlock() {
	DropBlock();
}
void Controls::DropBlock()
{
	currentBlock.Move(BlockDropDistance(), 0);
}
void Controls::LockBlock()
{
	for (Position cell : currentBlock.GetCellPosition())
		grid.grid[cell.row][cell.column] = { currentBlock.id };

	currentBlock = GetRandomBlock();
	currentBlock.ResetPosition();
	isHoldUsed = { false };
	grid.ClearFullRows();
}
