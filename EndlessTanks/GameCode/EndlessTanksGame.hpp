#pragma once

#include <list>

#include "../BaseAppEngine/Game.hpp"
#include "../BaseAppEngine/Window.hpp"
#include "Tanks/Tank.hpp"
#include "Weapons/Projectiles/BaseProjectile.hpp"

class EndlessTanksGame : public Game
{
private:
    // Helper functions

    bool mContentLoaded;

    Tank* mpTank;
    std::list<BaseProjectile*> lpProjectiles;

protected:
    /**
     *  Update the game logic.
     */
    virtual void OnUpdate(UpdateEventArgs& e) override;

    /**
     *  Render stuff.
     */
    virtual void OnRender(RenderEventArgs& e) override;

    /**
     * Invoked by the registered window when a key is pressed
     * while the window has focus.
     */
    virtual void OnKeyPressed(KeyEventArgs& e) override;

    virtual void OnResize(ResizeEventArgs& e) override;

    /**
     * Invoked when tank Fire.
    */
    void OnAddProjectile(BaseProjectile* projectile);

public:
    using base = Game;

    EndlessTanksGame(const std::wstring& name, int width, int height);
    /**
     *  Load content required for the demo.
     */
    virtual bool LoadContent() override;

    /**
     *  Unload demo specific content that was loaded in LoadContent.
     */
    virtual void UnloadContent() override;
};
