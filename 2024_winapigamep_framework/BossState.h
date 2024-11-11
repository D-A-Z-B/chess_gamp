#pragma once

class BossStateMachine;
class Boss;
class BossState
{
protected:
	BossStateMachine* stateMachine;
	Boss* boss;
public:
	BossState(Boss* boss, BossStateMachine* stateMachine);
	~BossState();
public:
	virtual void Enter();
	virtual void UpdateState();
	virtual void Exit();
};

