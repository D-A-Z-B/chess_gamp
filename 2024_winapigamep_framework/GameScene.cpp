#include "pch.h"
#include "GameScene.h"
#include "Ground.h"
#include "Player.h"
#include "Aim.h"
void GameScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 520.f });
	pPlayer->SetSize({ 10.f,10.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pGround = new Ground;
	pGround->SetPos({ SCREEN_WIDTH / 2.f,650.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 150.f });
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::Ground);

	Object* pAim = new Aim;
	AddObject(pAim, LAYER::AIM);
}
