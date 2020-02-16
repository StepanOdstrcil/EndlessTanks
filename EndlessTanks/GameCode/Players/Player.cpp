#include "Player.hpp"

Player::Player()
	: pTank(NULL)
{
}

Player::~Player()
{
}

void Player::OnForward()
{
	pTank->Forward();
}

void Player::OnBackward()
{
	pTank->Backward();
}

void Player::OnRight()
{
	pTank->TurnRight();
}

void Player::OnLeft()
{
	pTank->TurnLeft();
}

void Player::OnFire()
{
	pTank->Fire();
}
