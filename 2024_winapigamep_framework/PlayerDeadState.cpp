#include "pch.h"
#include "PlayerDeadState.h"
#include "Player.h"

void PlayerDeadState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::DEAD);
}

void PlayerDeadState::UpdateState()
{
}

void PlayerDeadState::Exit()
{
}
