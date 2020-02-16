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
	D2D1_RECT_F mTankOutlineRect;
	Position mPositions[4];
	BaseCanon* mpCanon;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mBrush;

protected:
	static const float TankWidth;
	static const float TankHeight;
	static const float TankHalfWidth;
	static const float TankHalfHeight;


	const D2D1::ColorF mTankColor;

	void Turn(float angleRad);
	void Move(float dX, float dY);

public:
	Tank(Position position, D2D1::ColorF color);
	~Tank();

	void Forward();
	void Backward();
	void TurnLeft();
	void TurnRight();
	BaseProjectile* Fire();

	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};

//Microsoft::WRL::ComPtr<IWICImagingFactory> mpIWICFactory;
//Microsoft::WRL::ComPtr<ID2D1Bitmap> mpBitmap;
