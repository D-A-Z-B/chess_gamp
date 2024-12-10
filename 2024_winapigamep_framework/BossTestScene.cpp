#include "pch.h"
#include "BossTestScene.h"
#include "Boss.h"
#include "Player.h"
#include "Ground.h"
#include "CollisionManager.h"
#include "TimeManager.h"

#include "Text.h"

#include "Background.h"
#include "Portal.h"

void BossTestScene::Init()
{
	Scene::Init();

	wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	Boss* pBoss = new Boss();
	pBoss->SetName(L"Boss");
	pBoss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
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
	pBackground->SetSize({ 1920, 1920 });
	pBackground->SetBackgroundTexture(L"board_plain_04");
	AddObject(pBackground, LAYER::BACKGROUND);

	Ground* pGround = new Ground();
	pGround->SetPos({ SCREEN_WIDTH / 2.f,650.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 150.f });
	AddObject(pGround, LAYER::Ground);

	Text* moveText = new Text();
	moveText->SetPos({ 100, 625 });
	moveText->SetSize({ 90.f, 0.f });
	moveText->SetText(L"MOVE: AD");
	moveText->SetColor(RGB(255, 255, 255));
	Vec2 moveTextSize = moveText->GetSize();
	moveText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", moveTextSize.x / 2);
	AddObject(moveText, LAYER::UI);

	Text* jumpText = new Text();
	jumpText->SetPos({ 120, 675 });
	jumpText->SetSize({ 90.f, 0.f });
	jumpText->SetText(L"JUMP: SPACE");
	jumpText->SetColor(RGB(255, 255, 255));
	Vec2 jumpTextSize = jumpText->GetSize();
	jumpText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", jumpTextSize.x / 2);
	AddObject(jumpText, LAYER::UI);

	Text* dashText = new Text();
	dashText->SetPos({ 370, 625 });
	dashText->SetSize({ 90.f, 0.f });
	dashText->SetText(L"DASH: SHIFT");
	dashText->SetColor(RGB(255, 255, 255));
	Vec2 dashTextSize = dashText->GetSize();
	dashText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", dashTextSize.x / 2);
	AddObject(dashText, LAYER::UI);

	Text* attackText = new Text();
	attackText->SetPos({ 380, 675 });
	attackText->SetSize({ 90.f, 0.f });
	attackText->SetText(L"ATTACK: LMB");
	attackText->SetColor(RGB(255, 255, 255));
	Vec2 attackTextSize = attackText->GetSize();
	attackText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", attackTextSize.x / 2);
	AddObject(attackText, LAYER::UI);

	Text* interactText = new Text();
	interactText->SetPos({ 640, 625 });
	interactText->SetSize({ 90.f, 0.f });
	interactText->SetText(L"INTERACT: W");
	interactText->SetColor(RGB(255, 255, 255));
	Vec2 interactTextSize = interactText->GetSize();
	interactText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", interactTextSize.x / 2);
	AddObject(interactText, LAYER::UI);

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
	GET_SINGLE(ResourceManager)->LoadSound(L"noise", L"Sound\\noise.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"GameBGM", L"Sound\\GameBGM.mp3", true);
	GET_SINGLE(ResourceManager)->LoadSound(L"ClearBGM", L"Sound\\ClearBGM.mp3", true);

	GET_SINGLE(ResourceManager)->Play(L"GameBGM", SOUND_CHANNEL::BGM);
}