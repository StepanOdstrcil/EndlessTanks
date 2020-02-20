#pragma once

#include <d2d1.h>
#include <wrl.h>

#include "../BaseGameComponents/IBaseGameComponents.hpp"
#include "../../Helpers/HighResolutionClock.hpp"
#include "../../Helpers/Events.hpp"
#include "Projectiles/BaseProjectile.hpp"

class BaseCanon : public Movable, public IGameComponent
{
private:
	HighResolutionClock mClock;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mColorBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mOutlineColorBrush;

	D2D1_RECT_F mCanonRect;
	D2D1_RECT_F mTowerRect;

protected:
	Position mCanonCollisionPositions[4];

public:
	BaseCanon(Position centerPosition, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush);
	virtual ~BaseCanon();

	virtual BaseProjectile* Fire();
	virtual bool CanFire();

	virtual void Move(const Velocity& velocity);

	// Dìdí se pøes Movable.
	virtual void Rotate(const float angleIncrementRad) override;
	virtual void Rotate(const D2D1::Matrix3x2F& rotationTransform) override;

	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
