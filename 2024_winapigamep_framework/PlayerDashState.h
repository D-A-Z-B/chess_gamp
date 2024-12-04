#pragma once
#include "PlayerState.h"
class PlayerDashState :
	public PlayerState
{
public:
	PlayerDashState(Player* player, StateMachine<PLAYER_STATE>* stateMachine, wstring animation)
		: PlayerState(player, stateMachine, animation) { }
	~PlayerDashState() {}
public:
	void Enter() override;
	void UpdateState() override;
	void Exit() override;
private:
	float dashPower = 5000.f;
	float dashTimer = 0;
	float dashTime;
};

