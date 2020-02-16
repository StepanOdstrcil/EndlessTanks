#include "BaseCanon.hpp"
#include "../../BaseAppEngine/Application.hpp"

BaseCanon::BaseCanon(D2D1_POINT_2F centerPosition, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> colorBrush, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> outlineColorBrush)
	: mClock()
	, mColorBrush(colorBrush)
	, mOutlineColorBrush(outlineColorBrush)
{
	mCanonPoints[0] = D2D1::Point2F(centerPosition.x, centerPosition.y);
	mCanonPoints[1] = D2D1::Point2F(centerPosition.x, centerPosition.y - 45 - 20.f);
}

BaseCanon::~BaseCanon()
{
}

BaseProjectile* BaseCanon::Fire()
{
	if (CanFire())
	{
		mClock.Reset();

		float angleRad = atan2f(mCanonPoints[1].x - mCanonPoints[0].x, mCanonPoints[1].y - mCanonPoints[0].y);

		return new BaseProjectile(Position(mCanonPoints[1].x, mCanonPoints[1].y), angleRad, mColorBrush, mOutlineColorBrush);
	}

	return nullptr;
}

bool BaseCanon::CanFire()
{
	return mClock.GetTotalMilliSeconds() > 500;
}

void BaseCanon::SetPosition(D2D1::Matrix3x2F& translationTranform)
{
	for (D2D1_POINT_2F& p : mCanonPoints)
	{
		p = p * translationTranform;
	}
}

void BaseCanon::Rotate(D2D1::Matrix3x2F& rotationTransform)
{
	for (D2D1_POINT_2F& p : mCanonPoints)
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

	renderTarget->DrawLine(mCanonPoints[0], mCanonPoints[1], mColorBrush.Get());
}
