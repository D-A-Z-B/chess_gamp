#include "pch.h"
#include "Define.h"
#include "Player.h"
#include "PlayerJumpState.h"
#include "InputManager.h"
#include "TimeManager.h"

void PlayerJumpState::Enter()
{
	std::cout << "jump\n";
	player->SetCurrentStateEnum(PLAYER_STATE::JUMP);

	player->yVelocity = -m_jumpPower;
	stateMachine->ChangeState(PLAYER_STATE::IDLE);
}

void PlayerJumpState::UpdateState()
{
}

void PlayerJumpState::Exit()
{
}
