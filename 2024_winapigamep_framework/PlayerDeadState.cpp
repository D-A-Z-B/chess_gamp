#include "pch.h"
#include "PlayerDeadState.h"
#include "Player.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DiePanel.h"

#include "ResourceManager.h"

void PlayerDeadState::Enter()
{
	player->SetCurrentStateEnum(PLAYER_STATE::DEAD);
	player->SetDead();

	GET_SINGLE(SceneManager)->GetCurrentScene()->StartSceneBlending(0.5f, 150, false);
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	GET_SINGLE(ResourceManager)->Play(L"PlayerDead", SOUND_CHANNEL::PLAYER);

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
