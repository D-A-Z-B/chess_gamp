#pragma once
#include "StateMachine.h"
#include "State.h"

class Player;

class PlayerState : public State<PLAYER_STATE>
{
public:
	PlayerState(Player* player, StateMachine<PLAYER_STATE>* stateMachine, wstring animation)
		: player(player), stateMachine(stateMachine), animation(animation) { };
	virtual ~PlayerState();
public:
	void Enter() override;
	void UpdateState() override;
	void Exit() override;
protected:
	StateMachine<PLAYER_STATE>* stateMachine;
	Player* player;
	wstring animation;
};

