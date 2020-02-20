#pragma once

#include <d2d1.h>

#include "Position.hpp"
#include "Velocity.hpp"
#include "IBaseGameComponents.hpp"

constexpr float PI = 3.14159265359f;
constexpr float RAD_CIRCLE = 2 * PI;
constexpr float DEG_TO_RAD = RAD_CIRCLE / 360;
constexpr float RAD_TO_DEG = 360 / RAD_CIRCLE;

class Movable : public IGameUpdatable
{
protected:
	void FixAngle();

	D2D1::Matrix3x2F GetRotationTransform(float angleRad);

public:
	static const float FullCircleRad;

	float mAngleRad;
	Position mPosition;
	Velocity mVelocity;

	Movable();
	Movable(Position position);
	Movable(Position position, Velocity velocity, float angleRad = 0.f);

	virtual void Rotate(const float angleIncrementRad);
	virtual void Rotate(const D2D1::Matrix3x2F& rotationTransform) = 0;

	// Dìdí se pøes IGameUpdatable.
	virtual void OnUpdate(UpdateEventArgs& e) override;
};
