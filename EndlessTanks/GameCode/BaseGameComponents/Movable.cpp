#include "Movable.hpp"

Movable::Movable() : Movable(Position(), Velocity())
{
}

Movable::Movable(Position position) : Movable(position, Velocity())
{
}

Movable::Movable(Position position, Velocity velocity, float angleRad)
	: mPosition(position)
	, mVelocity(velocity)
	, mAngleRad(angleRad)
{
}

void Movable::OnUpdate(UpdateEventArgs& e)
{
	mPosition.UpdatePosition(mVelocity);
}
