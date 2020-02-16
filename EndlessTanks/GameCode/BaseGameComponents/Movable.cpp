#include "Movable.hpp"

const float Movable::FullCircleRad = 2 * 3.14159265359f;

void Movable::FixAngle()
{
	if (mAngleRad > FullCircleRad)
	{
		mAngleRad -= FullCircleRad;
	}
	else if (mAngleRad < 0)
	{
		mAngleRad += FullCircleRad;
	}
}

D2D1::Matrix3x2F Movable::GetRotationTransform(float angleRad)
{
	return D2D1::Matrix3x2F::Rotation(angleRad * RAD_TO_DEG, mPosition);
}

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
