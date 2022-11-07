#pragma once
#include "SDL.h"

class Collision {
public:
	// AABB means Axis Aligned Bounding Box (type of collision detecting algorithm)
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};