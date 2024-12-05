#include "pch.h"
#include "DiePanel.h"
#include "Text.h"
#include "ResourceManager.h"

DiePanel::DiePanel()
	:gameOverTxt(nullptr)
{
	wstring path = GET_SINGLE(ResourceManager)->GetResPath();

	gameOverTxt = new Text();
	gameOverTxt->SetPos({ SCREEN_WIDTH / 2, 150 });
	gameOverTxt->SetText(L"Game Over");
	gameOverTxt->SetSize({ 300, 0 });
	gameOverTxt->SetColor(RGB(255, 0, 0));
	Vec2 vSize = gameOverTxt->GetSize();
	gameOverTxt->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", vSize.x / 2);
	gameOverTxt->Init();
	m_txtObj.push_back(gameOverTxt);
}

DiePanel::~DiePanel()
{
	delete gameOverTxt;
}

void DiePanel::Update()
{
}

void DiePanel::Render(HDC _hdc)
{
	for (size_t i = 0; i < m_txtObj.size(); ++i)
	{
		m_txtObj[i]->Render(_hdc);
	}
}
