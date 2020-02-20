#pragma once

#include <d2d1.h>
#include <wrl.h>

#include "../../BaseGameComponents/Movable.hpp"
#include "../../BaseGameComponents/IBaseGameComponents.hpp"
#include "../../../Helpers/HighResolutionClock.hpp"

class BaseProjectile : public Movable, public IGameComponent
{
private:
	double mLifeTimeMs;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mColorBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mOutlineColorBrush;
	D2D1_ELLIPSE mElipse;

protected:
	HighResolutionClock mClock;

public:
	static const float BaseProjectileRadius;

	BaseProjectile(Position position, float angleRad, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush);
	virtual ~BaseProjectile();

	bool HasLifeTimeEnded();

	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;

	// Dìdí se pøes Movable.
	virtual void Rotate(const D2D1::Matrix3x2F& rotationTransform) override;
};
