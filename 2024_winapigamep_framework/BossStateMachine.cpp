#include "pch.h"
#include "BossStateMachine.h"

BossStateMachine::~BossStateMachine()
{
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
