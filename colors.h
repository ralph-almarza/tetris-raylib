#pragma once
#include <raylib.h> // in order to use the 'Color' struct
#include <vector>

// 'extern' keyword was used to declare a variable in this file 
// and to use it in another file

// variables are declared here but not defined
// see implementation file (colors.cpp) for color definitions

extern const Color darkGrey;
extern const Color cyan;
extern const Color yellow;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color blue;
extern const Color purple;

std::vector<Color> GetCellColors() noexcept;