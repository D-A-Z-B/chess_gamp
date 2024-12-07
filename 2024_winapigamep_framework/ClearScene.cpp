#include "pch.h"
#include "ClearScene.h"

#include "Text.h"
#include "Ground.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "EventManager.h"

void ClearScene::Init()
{
	StartSceneBlending(0, 0, false);

	wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	Text* pTitle = new Text();
	pTitle->SetPos({ SCREEN_WIDTH / 2, 150 });
	pTitle->SetText(L"Clear !");
	pTitle->SetSize({ 1000, 0 });
	pTitle->SetColor(RGB(255, 255, 255));
	Vec2 vSize = pTitle->GetSize();
	pTitle->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	pTitle->Init();
	titleText = pTitle;
	AddObject(pTitle, LAYER::UI);

	Text* gotoTitle = new Text();
	gotoTitle->SetText(L"Goto title");
	gotoTitle->SetPos({ SCREEN_WIDTH / 2, 375 });
	gotoTitle->SetColor(RGB(0, 0, 0));
	gotoTitle->Init();
	vecButtons.push_back(gotoTitle);
	AddObject(gotoTitle, LAYER::UI);

	Text* reStart = new Text();
	reStart->SetText(L"Restart");
	reStart->SetPos({ SCREEN_WIDTH / 2, 500 });
	reStart->SetColor(RGB(0, 0, 0));
	reStart->Init();
	vecButtons.push_back(reStart);
	AddObject(reStart, LAYER::UI);

	Text* Exit = new Text();
	Exit->SetText(L"Exit");
	Exit->SetPos({ SCREEN_WIDTH / 2, 625 });
	Exit->SetColor(RGB(0, 0, 0));
	Exit->Init();
	vecButtons.push_back(Exit);
	AddObject(Exit, LAYER::UI);

	Object* pGround = new Ground;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
	pGround->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
	AddObject(pGround, LAYER::Ground);

	isStart = true;
}

void ClearScene::Update()
{
	if (isStart) {
		StartRoutine();
	}
	else if (isButton) {
		ButtonRoutine();
	}
	else {
		NormalRoutine();
	}
}

void ClearScene::StartRoutine()
{
	static wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	static float elapsedTime = 0;
	float time = 0.5f;

	float startSize = 1000;
	float targetX = 500;

	static bool isSoundPlay = false;

	if (isSoundPlay == false) {
		// 사운드 출력
	}

	if (elapsedTime < time) {
		float t = elapsedTime / time;
		float calcT = easeOutElastic(t);

		float x = startSize * (1 - calcT) + targetX * calcT;

		titleText->SetSize({ x, 0.f });

		titleText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", titleText->GetSize().x / 2);
		elapsedTime += fDT;
	}
	else {
		isSoundPlay = true;
		isStart = false;
		isButton = true;
		elapsedTime = 0;
	}
}

void ClearScene::ButtonRoutine()
{
	static wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	static float elapsedTime = 0;
	float time = 0.5f;

	float startX = 0;
	float endX = 125;

	if (elapsedTime < time) {
		float t = elapsedTime / time;
		float x = startX * (1 - t) + endX * t;
		for (int i = 0; i < vecButtons.size(); ++i) {
			vecButtons[i]->SetSize({ x, 0.f });
			vecButtons[i]->SetColor(RGB(255, 255, 255));
			vecButtons[i]->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vecButtons[i]->GetSize().x / 2);
		}
		elapsedTime += fDT;
	}
	else {
		isButton = false;
		elapsedTime = 0;
	}
}

void ClearScene::NormalRoutine()
{
	for (int i = 0; i < vecButtons.size(); ++i) {
		wstring path = GET_SINGLE(ResourceManager)->GetResPath();
		if (currentSelectedNumber == i) {
			vecButtons[i]->SetSize({ { 175, 0 } });
		}
		else {
			vecButtons[i]->SetSize({ { 125, 0 } });
		}
		vecButtons[i]->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vecButtons[i]->GetSize().x / 2);
	}

	if (GET_KEYDOWN(KEY_TYPE::ENTER)) {
		if (vecButtons[currentSelectedNumber]->GetCurrentText() == L"Goto title") {
			GET_SINGLE(EventManager)->ChangeScene(L"TitleScene");
		}
		else if (vecButtons[currentSelectedNumber]->GetCurrentText() == L"Restart") {
			GET_SINGLE(EventManager)->ChangeScene(L"BossTestScene");
		}
		else if (vecButtons[currentSelectedNumber]->GetCurrentText() == L"Exit") {
			GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
			std::exit(0);
		}
		vecButtons.clear();
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
}

float ClearScene::easeOutElastic(float t) {
	float c4 = (2 * PI) / 3;

	return t == 0
		? 0
		: t == 1
		? 1
		: pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
}
