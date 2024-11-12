#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"

void BossTestScene::Init()
{
	Boss* pBoss = new Boss();
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 100.f });
	pBoss->SetSize({ 160.f, 320.f });
	pBoss->ComponentInitialize();
	AddObject(pBoss, LAYER::BOSS);
}
