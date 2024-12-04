#include "pch.h"
#include "Aim.h"
#include "InputManager.h"
#include "Texture.h"
#include "ResourceManager.h"

Aim::Aim()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Aim", L"Texture\\Player\\Aim.bmp");
}

Aim::~Aim()
{
}

void Aim::Update()
{
	SetPos(GET_MOUSEPOS);
}

void Aim::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(vPos.x - vSize.x / 2)
		, (int)(vPos.y - vSize.y / 2)
		, vSize.x, vSize.y,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}
