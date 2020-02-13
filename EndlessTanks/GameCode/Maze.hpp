#pragma once

#include "BaseGameComponents/IBaseGameComponents.hpp"

class Maze : public IGameComponent
{
public:
	// Dìdí se pøes IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
