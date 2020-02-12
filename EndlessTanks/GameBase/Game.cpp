#include "../Helpers/D2D1LibPCH.hpp"

#include "Application.hpp"
#include "Game.hpp"
#include "Window.hpp"

void Game::OnUpdate(UpdateEventArgs& e)
{
}

void Game::OnRender(RenderEventArgs& e)
{
}

void Game::OnKeyPressed(KeyEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnKeyReleased(KeyEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnMouseMoved(MouseMotionEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnMouseButtonPressed(MouseButtonEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnMouseButtonReleased(MouseButtonEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnMouseWheel(MouseWheelEventArgs& e)
{
    // By default, do nothing.
}

void Game::OnResize(ResizeEventArgs& e)
{
    mWidth = e.Width;
    mHeight = e.Height;
}

void Game::OnWindowDestroy()
{
    // If the Window which we are registered to is 
    // destroyed, then any resources which are associated 
    // to the window must be released.
    UnloadContent();
}

Game::Game(const std::wstring& name, int width, int height)
    : mName(name)
    , mWidth(width)
    , mHeight(height)
{
}

Game::~Game()
{
    assert(!mpWindow && "Use Game::Destroy() before destruction.");
}

bool Game::Initialize()
{
    //// Check for DirectX Math library support.
    //if (!DirectX::XMVerifyCPUSupport())
    //{
    //    MessageBoxA(NULL, "Failed to verify DirectX Math library support.", "Error", MB_OK | MB_ICONERROR);
    //    return false;
    //}

    mpWindow = Application::Get().CreateRenderWindow(mName, mWidth, mHeight);
    mpWindow->RegisterCallbacks(shared_from_this());
    mpWindow->Show();

    return true;
}

void Game::Destroy()
{
    Application::Get().DestroyWindow(mpWindow);
    mpWindow.reset();
}
