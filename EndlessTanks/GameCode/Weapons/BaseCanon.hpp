#pragma once

#include <d2d1.h>
#include <wrl.h>

#include "../BaseGameComponents/IBaseGameComponents.hpp"
#include "../../Helpers/HighResolutionClock.hpp"
#include "../../Helpers/Events.hpp"
#include "Projectiles/BaseProjectile.hpp"

class BaseCanon : public IGameComponent
{
private:
	D2D1_POINT_2F mCanonPoints[2];
	HighResolutionClock mClock;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mColorBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mOutlineColorBrush;

public:
	BaseCanon(D2D1_POINT_2F centerPosition, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush);
	virtual ~BaseCanon();

	virtual BaseProjectile* Fire();
	virtual bool CanFire();

	virtual void SetPosition(D2D1::Matrix3x2F& translationTranform);
	virtual void Rotate(D2D1::Matrix3x2F& rotationTransform);

	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
