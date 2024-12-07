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
	// red;
	wstring tempTextue = texture;
	if ((boss->GetDefaultHp() / 3) > boss->GetCurrentHp()) {
		tempTextue += L"_R";
	}
	// orange
	else if ((boss->GetDefaultHp() / 2) > boss->GetCurrentHp()) {
		tempTextue += L"_O";
	}
	// green
	else {
		tempTextue += L"_G";
	}

	boss->SetBossTexture(tempTextue);
}

void BossState::Exit()
{
}
