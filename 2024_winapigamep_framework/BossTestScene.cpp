#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"

void BossTestScene::Init()
{
	Boss* pBoss = new Boss();
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBoss->SetSize({ 100.f, 100.f });
	AddObject(pBoss, LAYER::BOSS);
}
