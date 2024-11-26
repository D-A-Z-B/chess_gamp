#include "pch.h"
#include "Boss.h"
#include "BossState.h"


BossState::~BossState()
{
}

void BossState::Enter()
{
}

void BossState::UpdateState()
{
	boss->SetBossTexture(texture);
}

void BossState::Exit()
{
}
