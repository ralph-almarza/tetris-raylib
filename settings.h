#pragma once
#include <raylib.h>

constexpr int WINDOW_HEIGHT = 1500;
constexpr int WINDOW_WIDTH = 1500;
constexpr int CELL_SIZE = 65;
constexpr int GRID_OFFSET = 1;

constexpr auto MOVE_LEFT = KEY_X;
constexpr auto MOVE_RIGHT = KEY_C;

constexpr auto ROTATE_CCW = KEY_COMMA;
constexpr auto ROTATE_CW = KEY_PERIOD;
constexpr auto ROTATE_180 = KEY_SLASH;

constexpr auto HARD_DROP = KEY_SPACE;
constexpr auto SOFT_DROP = KEY_N;
constexpr auto HOLD = KEY_LEFT_SHIFT;

constexpr auto DAS = 0.090f;	// milliseconds
constexpr auto ARR = 0.0f;	// milliseconds

	