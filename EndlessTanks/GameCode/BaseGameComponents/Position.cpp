#include "Position.hpp"

Position::Position() : Position(0.f, 0.f)
{
}

Position::Position(float x, float y) : X(x), Y(y)
{
}

void Position::UpdatePosition(Velocity& velocity)
{
	X += velocity.X;
	Y += velocity.Y;
}
