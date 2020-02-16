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
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mBrush;
	D2D1_ELLIPSE mElipse;

protected:
	HighResolutionClock mClock;

public:
	BaseProjectile(Position position, float angleRad, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush);
	virtual ~BaseProjectile();

	bool HasLifeTimeEnded();

	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
