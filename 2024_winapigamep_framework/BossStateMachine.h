#pragma once

#include "BossStateEnum.h"
#include "BossState.h"

class Boss;
class BossStateMachine
{
public:
	~BossStateMachine();
public:
	void Initialize(BossStateEnum startState, Boss* boss);
	void ChangeState(BossStateEnum newState);
	void AddState(BossStateEnum stateEnum, BossState* bossState);
public:
	BossState* CurrentState;
	BossState* GetCurrentState() { return CurrentState; }
public:
	map<BossStateEnum, BossState*> StateMap;
	Boss* boss;
};

