#pragma once

#include "../../Helpers/Events.hpp"

class IGameUpdatable
{
	virtual void OnUpdate(UpdateEventArgs& e) = 0;
};

class IGameDrawable
{
	virtual void OnRender(RenderEventArgs& e) = 0;
};

class IGameComponent : public IGameUpdatable, public IGameDrawable
{
public:
	virtual void OnUpdate(UpdateEventArgs& e) = 0;
	virtual void OnRender(RenderEventArgs& e) = 0;
};
