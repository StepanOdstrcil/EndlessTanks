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

	// D�d� se p�es IGameUpdatable.
	virtual void OnUpdate(UpdateEventArgs& e) override;
};
