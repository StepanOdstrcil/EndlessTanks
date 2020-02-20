#include <algorithm>

#include "BaseCanon.hpp"
#include "../../BaseAppEngine/Application.hpp"
#include "../Tanks/Tank.hpp"

BaseCanon::BaseCanon(Position centerPosition, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush)
	: Movable(centerPosition)
	, mClock()
	, mColorBrush(colorBrush)
	, mOutlineColorBrush(outlineColorBrush)
	, mCanonRect()
	, mTowerRect()
{
	float towerHalfLength = Tank::TankHalfWidth * 0.6f;
	mTowerRect.left = centerPosition.x - towerHalfLength;
	mTowerRect.top = centerPosition.y - towerHalfLength;
	mTowerRect.right = centerPosition.x + towerHalfLength;
	mTowerRect.bottom = centerPosition.y + towerHalfLength;

	mCanonCollisionPositions[0] = Position(centerPosition.x - 7, centerPosition.y - towerHalfLength);
	mCanonCollisionPositions[1] = Position(centerPosition.x - 7, centerPosition.y - towerHalfLength - Tank::TankHeight * 0.44f);
	mCanonCollisionPositions[2] = Position(centerPosition.x + 7, centerPosition.y - towerHalfLength - Tank::TankHeight * 0.44f);
	mCanonCollisionPositions[3] = Position(centerPosition.x + 7, centerPosition.y - towerHalfLength);

	mCanonRect.left = mCanonCollisionPositions[0].x;
	mCanonRect.top = centerPosition.y; // To the center to draw over outline
	mCanonRect.right = mCanonCollisionPositions[2].x;
	mCanonRect.bottom = mCanonCollisionPositions[2].y;
}

BaseCanon::~BaseCanon()
{
}

BaseProjectile* BaseCanon::Fire()
{
	if (CanFire())
	{
		mClock.Reset();

		std::pair<const FLOAT&, const FLOAT&> x = std::minmax(mCanonCollisionPositions[1].x, mCanonCollisionPositions[2].x);
		std::pair<const FLOAT&, const FLOAT&> y = std::minmax(mCanonCollisionPositions[1].y, mCanonCollisionPositions[2].y);

		Position projectilePosition = Position(x.first + (x.second - x.first) / 2, y.first + (y.second - y.first) / 2);
		projectilePosition.UpdatePosition(Velocity(BaseProjectile::BaseProjectileRadius * sinf(mAngleRad), -BaseProjectile::BaseProjectileRadius * cosf(mAngleRad)));

		return new BaseProjectile(projectilePosition, mAngleRad, mColorBrush, mOutlineColorBrush);
	}

	return nullptr;
}

bool BaseCanon::CanFire()
{
	return mClock.GetTotalMilliSeconds() > 500;
}

void BaseCanon::Move(const Velocity& velocity)
{
	mPosition.UpdatePosition(velocity);

	for (Position& p : mCanonCollisionPositions)
	{
		p.UpdatePosition(velocity);
	}

	mCanonRect.left += velocity.X;
	mCanonRect.top += velocity.Y;
	mCanonRect.right += velocity.X;
	mCanonRect.bottom += velocity.Y;

	mTowerRect.left += velocity.X;
	mTowerRect.top += velocity.Y;
	mTowerRect.right += velocity.X;
	mTowerRect.bottom += velocity.Y;
}

void BaseCanon::Rotate(const float angleIncrementRad)
{
	Movable::Rotate(angleIncrementRad);
}

void BaseCanon::Rotate(const D2D1::Matrix3x2F& rotationTransform)
{
	for (D2D1_POINT_2F& p : mCanonCollisionPositions)
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

	renderTarget->SetTransform(GetRotationTransform(mAngleRad));
	renderTarget->DrawRectangle(mTowerRect, mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
	renderTarget->FillRectangle(mCanonRect, mColorBrush.Get());
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->DrawLine(mCanonCollisionPositions[0], mCanonCollisionPositions[1], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
	renderTarget->DrawLine(mCanonCollisionPositions[1], mCanonCollisionPositions[2], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
	renderTarget->DrawLine(mCanonCollisionPositions[2], mCanonCollisionPositions[3], mOutlineColorBrush.Get(), Tank::TankOutlineStroke);
}
