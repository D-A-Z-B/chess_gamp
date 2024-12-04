#include "pch.h"
#include "Define.h"
#include "Player.h"
#include "PlayerJumpState.h"
#include "InputManager.h"
#include "TimeManager.h"

void PlayerJumpState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::JUMP);
	__super::Enter();

	player->yVelocity = -m_jumpPower;
}

void PlayerJumpState::UpdateState()
{
	Vec2 vPos = player->GetPos();
	if (GET_KEY(KEY_TYPE::A))
	{
		vPos.x -= player->moveSpeed * fDT;
		player->ChangePacing(-1);
	}
	else if (GET_KEY(KEY_TYPE::D))
	{
		vPos.x += player->moveSpeed * fDT;
		player->ChangePacing(1);
	}
	vPos.x = std::clamp(vPos.x, 20.f, (float)SCREEN_WIDTH - 20.f);
	player->SetPos(vPos);

	if (player->yVelocity != -m_jumpPower && player->GetPos().y >= GROUND)
	{
		stateMachine->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerJumpState::Exit()
{
}
