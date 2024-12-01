#include "pch.h"
#include "Define.h"
#include "Player.h"
#include "PlayerMoveState.h"
#include "InputManager.h"
#include "TimeManager.h"

void PlayerMoveState::Enter()
{
	std::cout << "move\n";
	player->SetCurrentStateEnum(PLAYER_STATE::MOVE);

	player->isMove = true;
	player->ChangeAnimation();
}

void PlayerMoveState::UpdateState()
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
	else
	{
		stateMachine->ChangeState(PLAYER_STATE::IDLE);
		return;
	}
	player->SetPos(vPos);
}

void PlayerMoveState::Exit()
{
	player->isMove = false;
	player->ChangeAnimation();
}
