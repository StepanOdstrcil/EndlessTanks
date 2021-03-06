#include "Tank.hpp"

#include <string>

//#include "../../resource.h"

#include "../../BaseAppEngine/Application.hpp"
#include "../../Helpers/Helpers.hpp"

const float Tank::Speed = 2.8f;
const float Tank::BackSpeed = 0.6f * Tank::Speed;
const float Tank::TankWidth = 66.f;
const float Tank::TankHeight = 90.f;
const float Tank::TankOutlineStroke = 0.06f * TankWidth;
const float Tank::TankHalfWidth = Tank::TankWidth / 2;
const float Tank::TankHalfHeight = Tank::TankHeight / 2;

void Tank::Move(const float dX, const float dY)
{
	Tank::Move(Velocity(dX, dY));
}

void Tank::Move(const Velocity& velocity)
{
	mPosition.UpdatePosition(velocity);

	for (Position& p : mPositions)
	{
		p.UpdatePosition(velocity);
	}

	mTankRect.left += velocity.X;
	mTankRect.top += velocity.Y;
	mTankRect.right += velocity.X;
	mTankRect.bottom += velocity.Y;

	mpCanon->Move(velocity);
}

Tank::Tank(Position position, D2D1::ColorF color)
	: Movable(position)
	, mTankColor(color)
	, mTankColorBrush(nullptr)
	, mTankOutlineColor(D2D1::ColorF(0.f, 0.f, 0.f))
	, mTankOutlineColorBrush(nullptr)
	, mpCanon(nullptr)
	, mTankRect()
{
	mPositions[0] = Position(mPosition.x - TankHalfWidth, mPosition.y - TankHalfHeight);
	mPositions[1] = Position(mPosition.x + TankHalfWidth, mPosition.y - TankHalfHeight);
	mPositions[2] = Position(mPosition.x + TankHalfWidth, mPosition.y + TankHalfHeight);
	mPositions[3] = Position(mPosition.x - TankHalfWidth, mPosition.y + TankHalfHeight);

	mTankRect.left = mPositions[0].x + TankOutlineStroke;
	mTankRect.top = mPositions[0].y + TankOutlineStroke;
	mTankRect.right = mPositions[2].x - TankOutlineStroke;
	mTankRect.bottom = mPositions[2].y - TankOutlineStroke;

	ThrowIfFailed(Application::Get().GetRenderTarget()->CreateSolidColorBrush(mTankColor, &mTankColorBrush));
	ThrowIfFailed(Application::Get().GetRenderTarget()->CreateSolidColorBrush(mTankOutlineColor, &mTankOutlineColorBrush));

	mpCanon = new BaseCanon(mPosition, mTankColorBrush, mTankOutlineColorBrush);
}

Tank::~Tank()
{
	delete mpCanon;
	mpCanon = nullptr;
}

void Tank::Forward()
{
	Move(Speed * sinf(mAngleRad), -Speed * cosf(mAngleRad));
}

void Tank::Backward()
{
	Move(BackSpeed * sinf(mAngleRad), BackSpeed * cosf(mAngleRad));
}

void Tank::TurnRight()
{
	Rotate(0.1f);
}

void Tank::TurnLeft()
{
	Rotate(-0.1f);
}

BaseProjectile* Tank::Fire()
{
	return mpCanon->Fire();
}

void Tank::Rotate(const float angleIncrementRad)
{
	Movable::Rotate(angleIncrementRad);

	D2D1::Matrix3x2F rotationTransform = GetRotationTransform(angleIncrementRad);
	for (D2D1_POINT_2F& p : mPositions)
	{
		p = p * rotationTransform;
	}

	mpCanon->Rotate(angleIncrementRad);
	mpCanon->Rotate(rotationTransform);
}

void Tank::Rotate(const D2D1::Matrix3x2F& rotationTransform)
{
}

void Tank::OnUpdate(UpdateEventArgs& e)
{
	Movable::OnUpdate(e);

	for (Position& p : mPositions)
	{
		p.UpdatePosition(mVelocity);
	}

	mpCanon->OnUpdate(e);
}

void Tank::OnRender(RenderEventArgs& e)
{
	auto renderTarget = Application::Get().GetRenderTarget();

	renderTarget->SetTransform(GetRotationTransform(mAngleRad));
	renderTarget->FillRectangle(mTankRect, mTankColorBrush.Get());
	renderTarget->DrawRectangle(mTankRect, mTankOutlineColorBrush.Get(), TankOutlineStroke);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	//for (int i = 0; i < 3; i++)
	//{
	//	renderTarget->DrawLine(mPositions[i], mPositions[i + 1], mTankColorBrush.Get());
	//}
	//renderTarget->DrawLine(mPositions[3], mPositions[0], mTankColorBrush.Get());

	mpCanon->OnRender(e);
}

/*

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)


BITMAP LOAD - Read access violation

// Locate the resource in the application's executable
ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mpIWICFactory)));

Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder = NULL;
Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pSource = NULL;
Microsoft::WRL::ComPtr<IWICStream> pStream = NULL;
Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter = NULL;
Microsoft::WRL::ComPtr<IWICBitmapScaler> pScaler = NULL;

HRSRC imageResHandle = NULL;
HGLOBAL imageResDataHandle = NULL;
void* pImageFile = NULL;
DWORD imageFileSize = 0;

// Locate the resource.
imageResHandle = FindResourceW(NULL, MAKEINTRESOURCEW(IDB_TANK), L"PNG");
ThrowIfFailed(imageResHandle ? S_OK : E_FAIL);

// Load the resource.
imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);
ThrowIfFailed(imageResDataHandle ? S_OK : E_FAIL);

// Lock it to get a system memory pointer.
pImageFile = LockResource(imageResDataHandle);
ThrowIfFailed(pImageFile ? S_OK : E_FAIL);

// Calculate the size.
imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);
ThrowIfFailed(imageFileSize ? S_OK : E_FAIL);

// Create a WIC stream to map onto the memory.
ThrowIfFailed(mpIWICFactory->CreateStream(&pStream));

// Initialize the stream with the memory pointer and size.
ThrowIfFailed(pStream->InitializeFromMemory(
	reinterpret_cast<BYTE*>(pImageFile),
	imageFileSize
));

// Create a decoder for the stream.
ThrowIfFailed(mpIWICFactory->CreateDecoderFromStream(
	pStream.Get(),
	NULL,
	WICDecodeMetadataCacheOnLoad,
	&pDecoder
));

// Create the initial frame.
ThrowIfFailed(pDecoder->GetFrame(0, &pSource));

// Convert the image format to 32bppPBGRA
// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
ThrowIfFailed(mpIWICFactory->CreateFormatConverter(&pConverter));

ThrowIfFailed(pConverter->Initialize(
	pSource.Get(),
	GUID_WICPixelFormat32bppPBGRA,
	WICBitmapDitherTypeNone,
	NULL,
	0.f,
	WICBitmapPaletteTypeMedianCut
));

//create a Direct2D bitmap from the WIC bitmap.
ThrowIfFailed(Application::Get().GetRenderTarget()->CreateBitmapFromWicBitmap(
	pConverter.Get(),
	NULL,
	&mpBitmap
));
*/
