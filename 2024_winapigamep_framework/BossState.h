#pragma once

#include "StateMachine.h"
#include "State.h"
class Boss;

class BossState : public State<BOSS_STATE>
{
protected:
	StateMachine<BOSS_STATE>* stateMachine;
	Boss* boss;
	wstring texture;
public:
	BossState(Boss* boss, StateMachine<BOSS_STATE>* stateMachine, std::wstring texture)
		: boss(boss), stateMachine(stateMachine), texture(texture) {};
	virtual ~BossState();
public:
	void Enter() override;
	void UpdateState() override;
	void Exit() override;
};

