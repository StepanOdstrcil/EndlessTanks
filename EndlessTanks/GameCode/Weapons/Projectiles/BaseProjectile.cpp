#include "BaseProjectile.hpp"
#include "../../../BaseAppEngine/Application.hpp"
#include "../../Tanks/Tank.hpp"

const float BaseProjectile::BaseProjectileRadius = 5.f;

BaseProjectile::BaseProjectile(Position position, float angleRad, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush)
	: Movable(position, Velocity(Tank::Speed * sinf(angleRad), -Tank::Speed* cosf(angleRad)))
	, mLifeTimeMs(10000)
	, mColorBrush(colorBrush)
	, mOutlineColorBrush(outlineColorBrush)
	, mElipse()
	, mClock()
{
	mElipse.point = position;
	mElipse.radiusX = mElipse.radiusY = BaseProjectileRadius;
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
	renderTarget->DrawEllipse(mElipse, mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
}

void BaseProjectile::Rotate(const D2D1::Matrix3x2F& rotationTransform)
{
}
