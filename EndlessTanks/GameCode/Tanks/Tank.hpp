#pragma once

#include <d2d1.h>
#include <wrl.h>

#include <wincodec.h> // For "Windows Imaging Component (WIC)"

#include "../BaseGameComponents/Movable.hpp"

class Tank : public Movable, public IGameComponent
{
private:
	D2D1_RECT_F mTankOutline;
	Microsoft::WRL::ComPtr<IWICImagingFactory> mpIWICFactory;

	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mpBrush;
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mpBitmap;

protected:
	static const float TankHalfWidth;
	static const float TankHalfHeight;

	const D2D1::ColorF mTankColor;

public:
	Tank(Position position, D2D1::ColorF color);
	~Tank();

	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
