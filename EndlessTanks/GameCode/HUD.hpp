#pragma once

#include "BaseGameComponents/IGameComponent.hpp"

class HUD : public IGameComponent
{
public:
	// D�d� se p�es IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};

