#include "EndlessTanksGame.hpp"

#include "../GameBase/Application.hpp"
#include "../Helpers/Helpers.hpp"
#include "../GameBase/Window.hpp"

#include <wrl.h>

#include <d2d1.h>

#include <algorithm> // For std::min and std::max.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

void EndlessTanksGame::OnUpdate(UpdateEventArgs& e)
{
    static uint64_t frameCount = 0;
    static double totalTime = 0.0;

    base::OnUpdate(e);

    // Frame counter
    totalTime += e.ElapsedTime;
    frameCount++;
    if (totalTime > 1.0)
    {
        double fps = frameCount / totalTime;

        char buffer[512];
        sprintf_s(buffer, "FPS: %f\n", fps);
        OutputDebugStringA(buffer);

        frameCount = 0;
        totalTime = 0.0;
    }

    // Update the game
}

void EndlessTanksGame::OnRender(RenderEventArgs& e)
{
    base::OnRender(e);

    auto renderTarget = Application::Get().GetRenderTarget();

    auto c = D2D1::ColorF(0.2f, 0.5f, 0.2f);
    renderTarget->Clear(c);
}

void EndlessTanksGame::OnKeyPressed(KeyEventArgs& e)
{
    base::OnKeyPressed(e);

    switch (e.Key)
    {
    case KeyCode::Escape:
        Application::Get().Quit(0);
        break;
    case KeyCode::Enter:
        if (e.Alt)
        {
        case KeyCode::F11:
            mpWindow->ToggleFullscreen();
            break;
        }
    }
}

void EndlessTanksGame::OnResize(ResizeEventArgs& e)
{
    if (e.Width != GetClientWidth() || e.Height != GetClientHeight())
    {
        base::OnResize(e);

        // Recalculate game size
    }
}

EndlessTanksGame::EndlessTanksGame(const std::wstring& name, int width, int height)
    : base(name, width, height)
	, mContentLoaded(false)
{
}

bool EndlessTanksGame::LoadContent()
{
    auto renderTarget = Application::Get().GetRenderTarget();



    // Content loaded
    mContentLoaded = true;
    return true;
}

void EndlessTanksGame::UnloadContent()
{
    // Content unloaded
    mContentLoaded = false;
}
