#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"
#include "Player.h"
#include "CollisionManager.h"
#include "TimeManager.h"

#include "Background.h"
#include "Portal.h"

void BossTestScene::Init()
{
	Scene::Init();

	Boss* pBoss = new Boss();
	pBoss->SetName(L"Boss");
	pBoss->SetPos({SCREEN_WIDTH / 2.f, 150.f });
	pBoss->SetSize({ 160.f, 320.f });
	pBoss->SetPatternDelayTime(3.f);
	pBoss->Initialize();
	AddObject(pBoss, LAYER::BOSS);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	Background* pBackground = new Background();
	pBackground->SetPos({ 500, 0 });
	pBackground->SetSize({1920, 1920});
	pBackground->SetBackgroundTexture(L"board_plain_04");
	AddObject(pBackground, LAYER::BACKGROUND);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BOSS, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::BOSS);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BOSS_ATTACK_OBJECT);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BOSS_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::PORTAL);

	GET_SINGLE(ResourceManager)->LoadSound(L"TakeDown", L"Sound\\Boss\\TakeDown.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Caution", L"Sound\\Boss\\Caution.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove", L"Sound\\Boss\\BossMove.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove_isFast", L"Sound\\Boss\\BossMove_isFast.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove_Knight", L"Sound\\Boss\\BossMove_Knight.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossMove_Rook", L"Sound\\Boss\\BossMove_Rook.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"KingMove", L"Sound\\Boss\\KingMove.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"KingAttack", L"Sound\\Boss\\KingAttack.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Boss_Hurt", L"Sound\\Boss\\Boss_Hurt.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BossDead", L"Sound\\Boss\\BossDead.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Queen_Attack", L"Sound\\Boss\\Queen_Attack.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"PlayerShootSound", L"Sound\\Player\\PlayerShootSound.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"PlayerDead", L"Sound\\Player\\PlayerDead.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"GameBGM", L"Sound\\GameBGM.mp3", true);

	GET_SINGLE(ResourceManager)->Play(L"GameBGM", SOUND_CHANNEL::BGM);
}

void BossTestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	Vec2 vPos = { SCREEN_WIDTH / 2.f,650.f };
	Utils::RenderRectColor(_hdc, vPos, SCREEN_WIDTH, 150.f, RGB(0, 0, 0));
}
