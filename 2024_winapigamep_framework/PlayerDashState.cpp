#include "pch.h"
#include "Define.h"
#include "Player.h"
#include "PlayerDashState.h"
#include "TimeManager.h"

void PlayerDashState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::DASH);
	__super::Enter();

	player->isDash = true;
}

void PlayerDashState::UpdateState()
{
	Vec2 vPos = player->GetPos();
	vPos.x += dashPower * player->isPacing * fDT;
	player->SetPos(vPos);

	dashTimer += fDT;
	if (dashTimer >= 0.05f)
	{
		dashTimer = 0;
		stateMachine->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerDashState::Exit()
{
	player->isDash = false;
}
