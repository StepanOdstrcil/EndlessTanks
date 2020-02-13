#pragma once

#include <d2d1.h>

#include "Position.hpp"
#include "Velocity.hpp"
#include "IBaseGameComponents.hpp"

class Movable : public IGameUpdatable
{
public:
	float mAngleRad;
	Position mPosition;
	Velocity mVelocity;

	Movable();
	Movable(Position position);
	Movable(Position position, Velocity velocity, float angleRad = 0.f);

	// D�d� se p�es IGameUpdatable.
	virtual void OnUpdate(UpdateEventArgs& e) override;
};
