#include "pch.h"
#include "PlayerDeadState.h"
#include "Player.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DiePanel.h"

void PlayerDeadState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::DEAD);
	player->SetDead();

	GET_SINGLE(SceneManager)->GetCurrentScene()->StartBlending(0.5f, 150, false);

	Object* pDiePanel = new DiePanel();
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pDiePanel, LAYER::UI);

	__super::Enter();
}

void PlayerDeadState::UpdateState()
{
}

void PlayerDeadState::Exit()
{
}
