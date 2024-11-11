#include "pch.h"
#include "BossState.h"
#include "Boss.h"

BossState::BossState(Boss* boss, BossStateMachine* stateMachine) 
	: boss(boss), stateMachine(stateMachine)
{

}

BossState::~BossState()
{
}

void BossState::Enter()
{
}

void BossState::UpdateState()
{
}

void BossState::Exit()
{
}
