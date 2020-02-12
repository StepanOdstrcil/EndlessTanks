#pragma once

#include "BaseGameComponents/IGameComponent.hpp"

class HUD : public IGameComponent
{
public:
	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};

