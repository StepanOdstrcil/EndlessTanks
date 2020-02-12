#pragma once

#include "Velocity.hpp"

class Position
{
public:
	float X;
	float Y;

	Position();
	Position(float x, float y);

	void UpdatePosition(Velocity& velocity);
};
