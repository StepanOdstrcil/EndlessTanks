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
	std::function<void()> FireEvent;

	virtual void ProcessEvent(KeyEventArgs& e) = 0;
};
