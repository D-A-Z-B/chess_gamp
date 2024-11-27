#include "pch.h"
#include "StateMachine.h"

//StateMachine::~StateMachine() {
//	for (auto& pair : StateMap) {
//		delete pair.second;
//	}
//	StateMap.clear();
//}
//
//
//void StateMachine::Initialize(T startState, Boss* boss)
//{
//	CurrentState = StateMap[startState];
//	this->boss = boss;
//	CurrentState->Enter();
//}
//
//void StateMachine::ChangeState(BOSS_STATE newState)
//{
//	CurrentState->Exit();
//	CurrentState = StateMap[newState];
//	CurrentState->Enter();
//}
