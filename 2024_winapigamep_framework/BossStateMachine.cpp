#include "pch.h"
#include "BossStateMachine.h"

BossStateMachine::~BossStateMachine() {
	for (auto& pair : StateMap) {
		delete pair.second;
	}
	StateMap.clear();
}


void BossStateMachine::Initialize(BOSS_STATE startState, Boss* boss)
{
	CurrentState = StateMap[startState];
	this->boss = boss;
	CurrentState->Enter();
}

void BossStateMachine::ChangeState(BOSS_STATE newState)
{
	CurrentState->Exit();
	CurrentState = StateMap[newState];
	CurrentState->Enter();
}
