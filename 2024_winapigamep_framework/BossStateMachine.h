#pragma once

#include "BossState.h"

class Boss;
class BossStateMachine
{
public:
	~BossStateMachine();
public:
	void Initialize(BOSS_STATE startState, Boss* boss);
	void ChangeState(BOSS_STATE newState);

	template <typename T>
	void AddState(BOSS_STATE stateEnum, T* bossState) {
		StateMap.insert({ stateEnum, bossState });
	}
public:
	BossState* CurrentState;
	BossState* GetCurrentState() { return CurrentState; }
public:
	map<BOSS_STATE, BossState*> StateMap;
	Boss* boss;
};

