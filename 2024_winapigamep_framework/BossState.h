#pragma once

class BossStateMachine;
class Boss;
class BossState
{
protected:
	BossStateMachine* stateMachine;
	Boss* boss;
	wstring texture;
public:
	BossState(Boss* boss, BossStateMachine* stateMachine, wstring texture);
	~BossState();
public:
	virtual void Enter();
	virtual void UpdateState();
	virtual void Exit();
};

