#include "pch.h"
#include "BossState.h"
#include "Boss.h"

BossState::BossState(Boss* boss, BossStateMachine* stateMachine, wstring texture) 
	: boss(boss), stateMachine(stateMachine), texture(texture)
{
}

BossState::~BossState()
{
}

void BossState::Enter()
{
	boss->SetBossTexture(texture);
}

void BossState::UpdateState()
{
}

void BossState::Exit()
{
}
