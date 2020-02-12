#pragma once

#include "Position.hpp"
#include "Velocity.hpp"
#include "IBaseGameComponents.hpp"

class Movable : public IGameUpdatable
{
public:
	Position mPosition;
	Velocity mVelocity;

	Movable();
	Movable(Position position);
	Movable(Position position, Velocity velocity);

	// Dìdí se pøes IGameUpdatable.
	virtual void OnUpdate(UpdateEventArgs& e) override;
};
