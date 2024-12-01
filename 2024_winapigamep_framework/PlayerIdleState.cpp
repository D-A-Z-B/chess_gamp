#include "pch.h"
#include "Define.h"
#include "PlayerIdleState.h"
#include "InputManager.h"
#include "Player.h"
#include "Animator.h"

void PlayerIdleState::Enter()
{
	std::cout << "idle\n";
	player->SetCurrentStateEnum(PLAYER_STATE::IDLE);
}

void PlayerIdleState::UpdateState()
{
	
}

void PlayerIdleState::Exit()
{

}
