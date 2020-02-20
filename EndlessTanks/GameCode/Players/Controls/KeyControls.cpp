#include "KeyControls.hpp"

KeyControls::KeyControls(KeyCode::Key forward, KeyCode::Key backward, KeyCode::Key right, KeyCode::Key left, KeyCode::Key fire)
	: mForwardKey(forward)
	, mBackwardKey(backward)
	, mRightKey(right)
	, mLeftKey(left)
	, mFireKey(fire)
{
}

KeyControls::~KeyControls()
{
}

void KeyControls::ProcessEvent(KeyEventArgs& e)
{
	if (e.State != KeyEventArgs::KeyState::Pressed)
	{
		return;
	}

	if (e.Key == mForwardKey && ForwardEvent)
	{
		ForwardEvent();
	}
	else if (e.Key == mBackwardKey && BackwardEvent)
	{
		BackwardEvent();
	}
	
	if (e.Key == mRightKey && RightEvent)
	{
		RightEvent();
	}
	else if (e.Key == mLeftKey && LeftEvent)
	{
		LeftEvent();
	}

	if (e.Key == mFireKey && FireEvent)
	{
		FireEvent();
	}
}
