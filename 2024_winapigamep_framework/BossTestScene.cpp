#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"
#include "Player.h"
#include "CollisionManager.h"

#include "Background.h"

void BossTestScene::Init()
{
	Boss* pBoss = new Boss();
	pBoss->SetPos({SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetSize({ 160.f, 320.f });
	pBoss->SetPatternDelayTime(3.f);
	pBoss->Initialize();
	AddObject(pBoss, LAYER::BOSS);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);

	Background* pBackground = new Background();
	pBackground->SetPos({ 500, 0 });
	pBackground->SetSize({1920, 1920});
	AddObject(pBackground, LAYER::BACKGROUND);
}
