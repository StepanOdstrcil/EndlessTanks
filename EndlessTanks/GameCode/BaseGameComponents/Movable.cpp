#include "Movable.hpp"

Movable::Movable()
{
}

Movable::Movable(Position position) : Movable(position, Velocity())
{
}

Movable::Movable(Position position, Velocity velocity)
	: mPosition(position)
	, mVelocity(velocity)
{
}

void Movable::OnUpdate(UpdateEventArgs& e)
{
	mPosition.UpdatePosition(mVelocity);
}
