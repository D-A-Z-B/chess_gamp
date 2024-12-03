#include "pch.h"
#include "PlayerDeadState.h"
#include "Player.h"

void PlayerDeadState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::DEAD);
	__super::Enter();
}

void PlayerDeadState::UpdateState()
{
}

void PlayerDeadState::Exit()
{
}
