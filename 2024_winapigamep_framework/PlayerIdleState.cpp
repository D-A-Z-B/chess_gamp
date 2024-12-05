#include "pch.h"
#include "Define.h"
#include "PlayerIdleState.h"
#include "InputManager.h"
#include "Player.h"
#include "Animator.h"

void PlayerIdleState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::IDLE);
	__super::Enter();
}

void PlayerIdleState::UpdateState()
{
	
}

void PlayerIdleState::Exit()
{

}
