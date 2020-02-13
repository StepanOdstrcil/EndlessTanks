#pragma once

#include "BaseGameComponents/IBaseGameComponents.hpp"

class Maze : public IGameComponent
{
public:
	// D�d� se p�es IGameComponent.
	virtual void OnUpdate(UpdateEventArgs& e) override;
	virtual void OnRender(RenderEventArgs& e) override;
};
