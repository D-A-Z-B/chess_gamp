#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "Text.h"
#include "EventManager.h"
#include "ResourceManager.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Update()
{
    POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
    Vec2 vSize = m_pText->GetSize();

    if (PtInRect(&m_rect, mousePos))
    {
        float pocusSize = GetSize().x * 1.15f;
        if(pocusSize != vSize.x)
        {
            ResizeText(pocusSize);
        }

        if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
        {
            OnClick();
        }
    }
    else if (vSize.x != GetSize().x)
    {
        ResizeText(GetSize().x);
    }
}

void Button::ResizeText(float newSize)
{
    wstring path = GET_SINGLE(ResourceManager)->GetResPath();
    Vec2 vSize = m_pText->GetSize();
    vSize.x = newSize;
    m_pText->SetSize(vSize);
    m_pText->LoadFont(path + L"Font\\Galmuri7.ttf", L"Galmuri7 Regular", newSize / 2);
}

void Button::Init()
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	m_rect =
	{
		static_cast<LONG>(vPos.x - vSize.x / 2.f),
		static_cast<LONG>(vPos.y - vSize.y / 2.f),
		static_cast<LONG>(vPos.x + vSize.x / 2.f),
		static_cast<LONG>(vPos.y + vSize.y / 2.f)
	};
}

void Button::OnClick()
{
	if (!loadScene.empty())
	{
		GET_SINGLE(EventManager)->ChangeScene(loadScene);
	}
}

void Button::SetText(Text* _text)
{
	m_pText = _text;
	m_pText->SetPos(GetPos());
	SetSize(m_pText->GetSize());
}

void Button::Render(HDC _hdc)
{
}
