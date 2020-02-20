#pragma once

#include <d2d1.h>

#include "Velocity.hpp"

typedef struct Position : public D2D1_POINT_2F
{
public:
	Position();
	Position(float x, float y);

	void UpdatePosition(const Velocity& velocity);
} Position;
