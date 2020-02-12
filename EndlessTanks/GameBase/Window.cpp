#include "../Helpers/D2D1LibPCH.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "Game.hpp"

Window::Window(HWND hWnd, const std::wstring& windowName, int clientWidth, int clientHeight)
	: mhWnd(hWnd)
	, mWindowName(windowName)
	, mClientWidth(clientWidth)
	, mClientHeight(clientHeight)
	, mIsFullscreen(false)
	, mFrameCounter(0)
{
	//Application& app = Application::Get();

	//m_IsTearingSupported = app.IsTearingSupported();

	//m_dxgiSwapChain = CreateSwapChain();
	//m_d3d12RTVDescriptorHeap = app.CreateDescriptorHeap(BufferCount, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//m_RTVDescriptorSize = app.GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	UpdateRenderTargetViews();
}

Window::~Window()
{
	// Window should be destroyed with Application::DestroyWindow before
	// the window goes out of scope.
	assert(!mhWnd && "Use Application::DestroyWindow before destruction.");
}

void Window::RegisterCallbacks(std::shared_ptr<Game> pGame)
{
    mpGame = pGame;

    return;
}

void Window::OnUpdate(UpdateEventArgs& e)
{
    mUpdateClock.Tick();

    if (auto pGame = mpGame.lock())
    {
        mFrameCounter++;

        UpdateEventArgs updateEventArgs(mUpdateClock.GetDeltaSeconds(), mUpdateClock.GetTotalSeconds());
        pGame->OnUpdate(updateEventArgs);
    }
}

void Window::OnRender(RenderEventArgs& e)
{
    mRenderClock.Tick();

    if (auto pGame = mpGame.lock())
    {
        PAINTSTRUCT ps;
        auto renderTarget = Application::Get().GetRenderTarget();
        
        BeginPaint(mhWnd, &ps);


        RenderEventArgs renderEventArgs(mRenderClock.GetDeltaSeconds(), mRenderClock.GetTotalSeconds());
        pGame->OnRender(renderEventArgs);


        ThrowIfFailed(renderTarget->EndDraw());
        EndPaint(mhWnd, &ps);
    }
}

void Window::OnKeyPressed(KeyEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnKeyPressed(e);
    }
}

void Window::OnKeyReleased(KeyEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnKeyReleased(e);
    }
}

void Window::OnMouseMoved(MouseMotionEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnMouseMoved(e);
    }
}

void Window::OnMouseButtonPressed(MouseButtonEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnMouseButtonPressed(e);
    }
}

void Window::OnMouseButtonReleased(MouseButtonEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnMouseButtonReleased(e);
    }
}

void Window::OnMouseWheel(MouseWheelEventArgs& e)
{
    if (auto pGame = mpGame.lock())
    {
        pGame->OnMouseWheel(e);
    }
}

void Window::OnResize(ResizeEventArgs& e)
{
    // Update the client size.
    if (mClientWidth != e.Width || mClientHeight != e.Height)
    {
        mClientWidth = std::max(1, e.Width);
        mClientHeight = std::max(1, e.Height);

        //Application::Get().Flush();

        //for (int i = 0; i < BufferCount; ++i)
        //{
        //    m_d3d12BackBuffers[i].Reset();
        //}

        //DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        //ThrowIfFailed(m_dxgiSwapChain->GetDesc(&swapChainDesc));
        //ThrowIfFailed(m_dxgiSwapChain->ResizeBuffers(BufferCount, m_ClientWidth,
        //    m_ClientHeight, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags));

        //m_CurrentBackBufferIndex = m_dxgiSwapChain->GetCurrentBackBufferIndex();

        UpdateRenderTargetViews();
    }

    if (auto pGame = mpGame.lock())
    {
        pGame->OnResize(e);
    }
}

void Window::UpdateRenderTargetViews()
{
    //auto device = Application::Get().GetRenderTarget();

    //CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_d3d12RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

    //for (int i = 0; i < BufferCount; ++i)
    //{
    //    ComPtr<ID3D12Resource> backBuffer;
    //    ThrowIfFailed(m_dxgiSwapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

    //    device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

    //    m_d3d12BackBuffers[i] = backBuffer;

    //    rtvHandle.Offset(m_RTVDescriptorSize);
    //}
}

HWND Window::GetWindowHandle() const
{
	return mhWnd;
}

void Window::Destroy()
{
	if (auto pGame = mpGame.lock())
	{
		// Notify the registered game that the window is being destroyed.
		pGame->OnWindowDestroy();
	}
	if (mhWnd)
	{
		DestroyWindow(mhWnd);
		mhWnd = nullptr;
	}
}

const std::wstring& Window::GetWindowName() const
{
	return mWindowName;
}

int Window::GetClientWidth() const
{
	return mClientWidth;
}

int Window::GetClientHeight() const
{
	return mClientHeight;
}

bool Window::IsFullScreen() const
{
	return mIsFullscreen;
}

void Window::SetFullscreen(bool fullscreen)
{
    if (mIsFullscreen != fullscreen)
    {
        mIsFullscreen = fullscreen;

        if (mIsFullscreen) // Switching to fullscreen.
        {
            // Store the current window dimensions so they can be restored 
            // when switching out of fullscreen state.
            ::GetWindowRect(mhWnd, &mWindowRect);

            // Set the window style to a borderless window so the client area fills
            // the entire screen.
            UINT windowStyle = WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

            ::SetWindowLongW(mhWnd, GWL_STYLE, windowStyle);

            // Query the name of the nearest display device for the window.
            // This is required to set the fullscreen dimensions of the window
            // when using a multi-monitor setup.
            HMONITOR hMonitor = ::MonitorFromWindow(mhWnd, MONITOR_DEFAULTTONEAREST);
            MONITORINFOEX monitorInfo = {};
            monitorInfo.cbSize = sizeof(MONITORINFOEX);
            ::GetMonitorInfo(hMonitor, &monitorInfo);

            ::SetWindowPos(mhWnd, HWND_TOPMOST,
                monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.top,
                monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE);

            ::ShowWindow(mhWnd, SW_MAXIMIZE);
        }
        else
        {
            // Restore all the window decorators.
            ::SetWindowLong(mhWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

            ::SetWindowPos(mhWnd, HWND_NOTOPMOST,
                mWindowRect.left,
                mWindowRect.top,
                mWindowRect.right - mWindowRect.left,
                mWindowRect.bottom - mWindowRect.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE);

            ::ShowWindow(mhWnd, SW_NORMAL);
        }
    }
}

void Window::ToggleFullscreen()
{
    SetFullscreen(!mIsFullscreen);
}

void Window::Show()
{
	::ShowWindow(mhWnd, SW_SHOW);
}

void Window::Hide()
{
	::ShowWindow(mhWnd, SW_HIDE);
}

UINT Window::Present()
{
    // Render in Direct3D
    // Here all rendering is in Window.OnRender directly

	return 0;
}
