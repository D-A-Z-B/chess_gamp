#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"
#include "Player.h"
#include "CollisionManager.h"

#include "Background.h"
#include "Ground.h"

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

	Background* pBackground = new Background();
	pBackground->SetPos({ 500, 0 });
	pBackground->SetSize({1920, 1920});
	AddObject(pBackground, LAYER::BACKGROUND);

	Object* pGround = new Ground;
	pGround->SetPos({ SCREEN_WIDTH / 2.f,650.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 150.f });
	AddObject(pGround, LAYER::Ground);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BOSS, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::BOSS);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BOSS_ATTACK_OBJECT);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BOSS_PROJECTILE);

	GET_SINGLE(ResourceManager)->LoadSound(L"TakeDown", L"Sound\\Boss\\TakeDown.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Caution", L"Sound\\Boss\\Caution.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove", L"Sound\\Boss\\BossMove.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove_isFast", L"Sound\\Boss\\BossMove_isFast.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove_Knight", L"Sound\\Boss\\BossMove_Knight.mp3", false);
}
