#include "pch.h"
#include "DiePanel.h"
#include "Text.h"
#include "ResourceManager.h"
#include "Button.h"

DiePanel::DiePanel()
{
	wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	//title
	Text* pOverText = new Text();
	pOverText->SetPos({ SCREEN_WIDTH / 2, 150 });
	pOverText->SetText(L"Game Over");
	pOverText->SetSize({ 300, 0 });
	pOverText->SetColor(RGB(255, 0, 0));
	Vec2 vSize = pOverText->GetSize();
	pOverText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	pOverText->Init();
	m_vObj.push_back(pOverText);

	//retry
	Text* pRetryText = new Text();
	pRetryText->SetText(L"Retry");
	pRetryText->SetSize({ 200, 80 });
	pRetryText->SetColor(RGB(255, 0, 0));
	vSize = pRetryText->GetSize();
	pRetryText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	pRetryText->Init();
	m_vObj.push_back(pRetryText);

	Button* pRetryButton = new Button();
	pRetryButton->SetPos({ SCREEN_WIDTH / 3, 640 });
	pRetryButton->SetText(pRetryText);
	pRetryButton->SetLoadingScene(L"BossTestScene");
	pRetryButton->Init();
	m_vObj.push_back(pRetryButton);

	//menu
	Text* pTitleText = new Text();
	pTitleText->SetText(L"Title");
	pTitleText->SetSize({ 200, 80 });
	pTitleText->SetColor(RGB(255, 0, 0));
	vSize = pTitleText->GetSize();
	pTitleText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	pTitleText->Init();
	m_vObj.push_back(pTitleText);

	Button* pTitleButton = new Button();
	pTitleButton->SetPos({ SCREEN_WIDTH / 3 * 2, 640 });
	pTitleButton->SetText(pTitleText);
	pTitleButton->SetLoadingScene(L"TitleScene");
	pTitleButton->Init();
	m_vObj.push_back(pTitleButton);
}

DiePanel::~DiePanel()
{
	for (UINT i = 0; i < m_vObj.size(); ++i)
	{
		delete m_vObj[i];
	}
	m_vObj.clear();
}

void DiePanel::Update()
{
	for (size_t i = 0; i < m_vObj.size(); ++i)
	{
		m_vObj[i]->Update();
	}
}

void DiePanel::Render(HDC _hdc)
{
	for (size_t i = 0; i < m_vObj.size(); ++i)
	{
		m_vObj[i]->Render(_hdc);
	}
}
