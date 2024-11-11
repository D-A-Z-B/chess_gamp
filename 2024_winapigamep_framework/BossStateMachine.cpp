#include "pch.h"
#include "BossStateMachine.h"

BossStateMachine::~BossStateMachine()
{
}

void BossStateMachine::Initialize(BossStateEnum startState, Boss* boss)
{
	CurrentState = StateMap[startState];
	this->boss = boss;
	CurrentState->Enter();
}

void BossStateMachine::ChangeState(BossStateEnum newState)
{
	CurrentState->Exit();
	CurrentState = StateMap[newState];
	CurrentState->Enter();
}

void BossStateMachine::AddState(BossStateEnum stateEnum, BossState* bossState)
{
	StateMap.insert(stateEnum, bossState);
}
