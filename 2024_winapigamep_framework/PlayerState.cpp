#include "pch.h"
#include "PlayerState.h"
#include "Player.h"

PlayerState::~PlayerState()
{
}

void PlayerState::Enter()
{
	player->ChangeAnimation(animation, player->currentStateEnum != PLAYER_STATE::DEAD);
}

void PlayerState::UpdateState()
{
}

void PlayerState::Exit()
{
}
