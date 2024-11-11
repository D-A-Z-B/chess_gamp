#include "pch.h"
#include "GameScene.h"
#include "Ground.h"
void GameScene::Init()
{
	Object* pGround = new Ground;
	pGround->SetPos({ SCREEN_WIDTH / 2.f,650.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 150.f });
	AddObject(pGround, LAYER::Ground);
}
