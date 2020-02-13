#include "Position.hpp"

Position::Position() : Position(0.f, 0.f)
{
}

Position::Position(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Position::UpdatePosition(Velocity& velocity)
{
	x += velocity.X;
	y += velocity.Y;
}
