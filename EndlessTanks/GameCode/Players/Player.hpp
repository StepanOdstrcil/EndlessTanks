#pragma once

#include "../Tanks/Tank.hpp"

class Player
{
protected:
	Tank* pTank;

public:
	Player();
	virtual ~Player();

	void OnForward();
	void OnBackward();
	void OnRight();
	void OnLeft();
	void OnFire();
};
