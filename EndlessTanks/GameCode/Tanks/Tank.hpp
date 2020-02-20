#pragma once

#include <d2d1.h>
#include <wrl.h>

#include <functional>

//#include <wincodec.h> // For "Windows Imaging Component (WIC)"

#include "../BaseGameComponents/Movable.hpp"
#include "../Weapons/BaseCanon.hpp"

class Tank : public Movable, public IGameComponent
{
private:
	D2D1_RECT_F mTankRect;
	Position mPositions[4];
	BaseCanon* mpCanon;

	const D2D1::ColorF mTankOutlineColor;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mTankOutlineColorBrush;
	const D2D1::ColorF mTankColor;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mTankColorBrush;

protected:
	void Move(const float dX, const float dY);
	void Move(const Velocity& velocity);

public:
	static const float Speed;
	static const float BackSpeed;
	static const float TankOutlineStroke;
	static const float TankWidth;
	static const float TankHeight;
	static const float TankHalfWidth;
	static const float TankHalfHeight;

	Tank(Position position, D2D1::ColorF color);
	~Tank();

	void Forward();
	void Backward();
	void TurnLeft();
	void TurnRight();
	BaseProjectile* Fire();

	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;

	// Dìdí se pøes Movable.
	virtual void Rotate(const float angleIncrementRad) override;
	virtual void Rotate(const D2D1::Matrix3x2F& rotationTransform) override;
};

//Microsoft::WRL::ComPtr<IWICImagingFactory> mpIWICFactory;
//Microsoft::WRL::ComPtr<ID2D1Bitmap> mpBitmap;
