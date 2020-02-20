#pragma once

#include "ITankControls.hpp"

class KeyControls : public ITankControls
{
protected:
	KeyCode::Key mForwardKey;
	KeyCode::Key mBackwardKey;
	KeyCode::Key mRightKey;
	KeyCode::Key mLeftKey;
	KeyCode::Key mFireKey;

public:
	KeyControls(KeyCode::Key forward, KeyCode::Key backward, KeyCode::Key right, KeyCode::Key left, KeyCode::Key fire);
	virtual ~KeyControls();

	// Dìdí se pøes ITankControls.
	virtual void ProcessEvent(KeyEventArgs& e) override;
};
