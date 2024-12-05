#include "pch.h"
#include "TitleScene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "EventManager.h"

#include "Background.h"
#include "Text.h"
#include "Ground.h"


TitleScene::~TitleScene()
{
	
}

void TitleScene::Init()
{
	Background* pBackground1 = new Background();

	wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	pBackground1->SetPos({ 0, 150 });
	pBackground1->SetSize({ 1280, 1280 });
	pBackground1->SetBackgroundTexture(L"board_plain_04_darkened");
	AddObject(pBackground1, LAYER::BACKGROUND);
	vecBackground.push_back(pBackground1);

	Background* pBackground2 = new Background();
	pBackground2->SetPos({ 1280, 150 });
	pBackground2->SetSize({ 1280, 1280 });
	pBackground2->SetBackgroundTexture(L"board_plain_04_darkened");
	AddObject(pBackground2, LAYER::BACKGROUND);
	vecBackground.push_back(pBackground2);

	Text* pText = new Text();
	pText->SetPos({ SCREEN_WIDTH / 2, 150});
	pText->SetText(L"Eternal Board");
	pText->SetSize({ 300, 0 });
	pText->SetColor(RGB(255, 255, 255));
	Vec2 vSize = pText->GetSize();
	pText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	pText->Init();
	AddObject(pText, LAYER::UI);

	Text* startText = new Text();
	startText->SetPos({ SCREEN_WIDTH / 2, 425 });
	startText->SetText(L"Start");
	startText->SetSize({ 175, 0 });
	startText->SetColor(RGB(255, 255, 255));
	Vec2 startTextSize = startText->GetSize();
	startText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", startTextSize.x / 2);
	startText->Init();
	AddObject(startText, LAYER::UI);
	vecButtons.push_back(startText);

	Text* exitText = new Text();
	exitText->SetPos({ SCREEN_WIDTH / 2, 550 });
	exitText->SetText(L"Exit");
	exitText->SetSize({ 175, 0 });
	exitText->SetColor(RGB(255, 255, 255));
	Vec2 exitTextSize = exitText->GetSize();
	exitText->LoadFont(L"C:\\Cpp\\chess_gamp\\Output\\build\\Resource\\Font\\Galmuri7.ttf", L"Galmuri7 Regular", exitTextSize.x / 2);
	exitText->Init();
	AddObject(exitText, LAYER::UI);
	vecButtons.push_back(exitText);

	GET_SINGLE(ResourceManager)->LoadSound(L"TitleBGM", L"Sound\\TitleBGM.mp3", true);
	GET_SINGLE(ResourceManager)->Play(L"TitleBGM", SOUND_CHANNEL::BGM);
}

void TitleScene::Update()
{
	Scene::Update();

	const float speed = -50.f * fDT;

	if (GET_KEYDOWN(KEY_TYPE::ENTER)) {
		if (vecButtons[currentSelectedNumber]->GetCurrentText() == L"Start") {
			GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
			GET_SINGLE(EventManager)->ChangeScene(L"BossTestScene");
		}
		else if (vecButtons[currentSelectedNumber]->GetCurrentText() == L"Exit") {
			GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
			std::exit(0);
		}
	}
	if (GET_KEYDOWN(KEY_TYPE::UP)) {
		currentSelectedNumber--;
		if (currentSelectedNumber < 0) {
			currentSelectedNumber = vecButtons.size() - 1;
		}
	}

	if (GET_KEYDOWN(KEY_TYPE::DOWN)) {
		currentSelectedNumber++;
		if (currentSelectedNumber >= vecButtons.size()) {
			currentSelectedNumber = 0;
		}
	}

	for (int i = 0; i < vecButtons.size(); ++i) {
		wstring path = GET_SINGLE(ResourceManager)->GetResPath();
		if (currentSelectedNumber == i) {
			vecButtons[i]->SetSize({ { 225, 0 } });
		}
		else {
			vecButtons[i]->SetSize({ { 175, 0 } });
		}
		vecButtons[i]->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vecButtons[i]->GetSize().x / 2);
	}

	for (Background* pBackground : vecBackground)
	{
		Vec2 vPos = pBackground->GetPos();
		vPos.x += speed;

		if (vPos.x <= -1280 / 2)
		{
			vPos.x += 1280 * 2;
		}

		pBackground->SetPos(vPos);
	}
}
