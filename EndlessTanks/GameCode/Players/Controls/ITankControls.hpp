#pragma once

#include <functional>

#include "../../../Helpers/Events.hpp"

class ITankControls
{
public:
	std::function<void()> ForwardEvent;
	std::function<void()> BackwardEvent;
	std::function<void()> RightEvent;
	std::function<void()> LeftEvent;

	virtual void ProcessEvent(KeyEventArgs& e) = 0;
};
