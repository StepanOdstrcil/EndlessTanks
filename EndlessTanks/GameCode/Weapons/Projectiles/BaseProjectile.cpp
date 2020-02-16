#include "BaseProjectile.hpp"
#include "../../../BaseAppEngine/Application.hpp"

BaseProjectile::BaseProjectile(Position position, float angleRad, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush)
	: Movable(position, Velocity(1.f * sinf(angleRad), 1.f * cosf(angleRad)))
	, mLifeTimeMs(10000)
	, mColorBrush(colorBrush)
	, mOutlineColorBrush(outlineColorBrush)
	, mElipse()
	, mClock()
{
	mElipse.point = position;
	mElipse.radiusX = mElipse.radiusY = 5.f;
}

BaseProjectile::~BaseProjectile()
{
}

bool BaseProjectile::HasLifeTimeEnded()
{
	return mClock.GetTotalMilliSeconds() > mLifeTimeMs;
}

void BaseProjectile::OnUpdate(UpdateEventArgs& e)
{
	Movable::OnUpdate(e);
	mElipse.point = mPosition;

	mClock.Tick();
}

void BaseProjectile::OnRender(RenderEventArgs& e)
{
	auto renderTarget = Application::Get().GetRenderTarget();

	renderTarget->FillEllipse(mElipse, mColorBrush.Get());
}
