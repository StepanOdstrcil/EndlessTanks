#include "BaseCanon.hpp"
#include "../../BaseAppEngine/Application.hpp"

BaseCanon::BaseCanon(D2D1_POINT_2F centerPosition, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush)
	: mClock()
	, mColorBrush(colorBrush)
	, mOutlineColorBrush(outlineColorBrush)
	, mCanonCanonRect()
	, mCanonTowerRect()
{
	mCollisionPositions[0] = D2D1::Point2F(centerPosition.x - 10, centerPosition.y);
	mCollisionPositions[1] = D2D1::Point2F(centerPosition.x - 10, centerPosition.y - 45 - 20.f);
	mCollisionPositions[2] = D2D1::Point2F(centerPosition.x + 10, centerPosition.y - 45 - 20.f);
	mCollisionPositions[3] = D2D1::Point2F(centerPosition.x + 10, centerPosition.y);

	mCanonTowerRect.left = 0;
	mCanonTowerRect.top = 0;
	mCanonTowerRect.right = 0;
	mCanonTowerRect.bottom = 0;
}

BaseCanon::~BaseCanon()
{
}

BaseProjectile* BaseCanon::Fire()
{
	if (CanFire())
	{
		mClock.Reset();

		float angleRad = atan2f(mCollisionPositions[1].x - mCollisionPositions[0].x, mCollisionPositions[1].y - mCollisionPositions[0].y);

		return new BaseProjectile(Position(mCollisionPositions[1].x, mCollisionPositions[1].y), angleRad, mColorBrush, mOutlineColorBrush);
	}

	return nullptr;
}

bool BaseCanon::CanFire()
{
	return mClock.GetTotalMilliSeconds() > 500;
}

void BaseCanon::SetPosition(D2D1::Matrix3x2F& translationTranform)
{
	for (D2D1_POINT_2F& p : mCollisionPositions)
	{
		p = p * translationTranform;
	}
}

void BaseCanon::Rotate(D2D1::Matrix3x2F& rotationTransform)
{
	for (D2D1_POINT_2F& p : mCollisionPositions)
	{
		p = p * rotationTransform;
	}
}

void BaseCanon::OnUpdate(UpdateEventArgs& e)
{
	mClock.Tick();
}

void BaseCanon::OnRender(RenderEventArgs& e)
{
	auto renderTarget = Application::Get().GetRenderTarget();

	renderTarget->DrawLine(mCollisionPositions[0], mCollisionPositions[1], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
	renderTarget->DrawLine(mCollisionPositions[1], mCollisionPositions[2], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
	renderTarget->DrawLine(mCollisionPositions[2], mCollisionPositions[3], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
}
