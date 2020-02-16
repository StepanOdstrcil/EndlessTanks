#include "EndlessTanksGame.hpp"

#include <wrl.h>
#include <d2d1.h>

#include <algorithm>

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#include "../BaseAppEngine/Application.hpp"
#include "../Helpers/Helpers.hpp"
#include "../BaseAppEngine/Window.hpp"

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
        sprintf_s(buffer, "FPS: %f; Total Time: %f\n", fps, e.TotalTime);
        OutputDebugStringA(buffer);

        frameCount = 0;
        totalTime = 0.0;
    }

    // Update the game

    mpTank->OnUpdate(e);

    for (BaseProjectile*& bp : lpProjectiles)
    {
        if (bp->HasLifeTimeEnded())
        {
            delete bp;
            bp = nullptr;
        }
        else
        {
            bp->OnUpdate(e);
        }
    }
    lpProjectiles.erase(std::remove(lpProjectiles.begin(), lpProjectiles.end(), nullptr), lpProjectiles.end());
}

void EndlessTanksGame::OnRender(RenderEventArgs& e)
{
    base::OnRender(e);

    auto renderTarget = Application::Get().GetRenderTarget();

    auto c = D2D1::ColorF(0.2f, 0.5f, 0.2f);
    renderTarget->Clear(c);

    // Render game components
    mpTank->OnRender(e);

    for (BaseProjectile*& bp : lpProjectiles)
    {
        bp->OnRender(e);
    }
}

void EndlessTanksGame::OnKeyPressed(KeyEventArgs& e)
{
    base::OnKeyPressed(e);

    BaseProjectile* bp;
    switch (e.Key)
    {
    case KeyCode::Key::Up:
        mpTank->Forward();
        break;
    case KeyCode::Key::Down:
        mpTank->Backward();
        break;
    case KeyCode::Key::Left:
        mpTank->TurnLeft();
        break;
    case KeyCode::Key::Right:
        mpTank->TurnRight();
        break;
    case KeyCode::Key::Space:
        // TEST
        bp = mpTank->Fire();
        if (bp)
            lpProjectiles.push_back(bp);
        break;
    case KeyCode::Key::Escape:
        Application::Get().Quit(0);
        break;
    case KeyCode::Key::Enter:
        if (e.Alt)
        {
        case KeyCode::Key::F11:
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

void EndlessTanksGame::OnAddProjectile(BaseProjectile* projectile)
{
    lpProjectiles.push_back(projectile);
}

EndlessTanksGame::EndlessTanksGame(const std::wstring& name, int width, int height)
    : base(name, width, height)
	, mContentLoaded(false)
    , mpTank(nullptr)
{
}

bool EndlessTanksGame::LoadContent()
{
    auto renderTarget = Application::Get().GetRenderTarget();

    mpTank = new Tank(Position(200, 200), D2D1::ColorF(1.f, 0.f, 0.f));

    // Content loaded
    mContentLoaded = true;

    return true;
}

void EndlessTanksGame::UnloadContent()
{
    delete mpTank;

    // Content unloaded
    mContentLoaded = false;
}
