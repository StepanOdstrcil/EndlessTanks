#include <string>

#include "../../resource.h"

#include "Tank.hpp"
#include "../../BaseAppEngine/Application.hpp"
#include "../../Helpers/Helpers.hpp"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

const float Tank::TankHalfWidth = 150.f / 2;
const float Tank::TankHalfHeight = 240.0f / 2;

Tank::Tank(Position position, D2D1::ColorF color)
	: Movable(position)
	, mTankColor(color)
	, mTankOutline()
	, mpBrush(nullptr)
	, mpBitmap(nullptr)
	, mpIWICFactory(nullptr)
{
	mTankOutline.left = mPosition.x - TankHalfWidth;
	mTankOutline.top = mPosition.y - TankHalfHeight;
	mTankOutline.right = mPosition.x + TankHalfWidth;
	mTankOutline.bottom = mPosition.y + TankHalfHeight;

	ThrowIfFailed(Application::Get().GetRenderTarget()->CreateSolidColorBrush(mTankColor, &mpBrush));

	// Bitmap
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
}

Tank::~Tank()
{
}

void Tank::OnUpdate(UpdateEventArgs& e)
{
	Movable::OnUpdate(e);

	mTankOutline.left = mPosition.x - TankHalfWidth;
	mTankOutline.top = mPosition.y - TankHalfHeight;
	mTankOutline.right = mPosition.x + TankHalfWidth;
	mTankOutline.bottom = mPosition.y + TankHalfHeight;
}

void Tank::OnRender(RenderEventArgs& e)
{
	auto renderTarget = Application::Get().GetRenderTarget();

	renderTarget->DrawBitmap(mpBitmap.Get(), mTankOutline);
	renderTarget->DrawRectangle(mTankOutline, mpBrush.Get());
}
