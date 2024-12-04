#include "pch.h"
#include "Background.h"

#include "Texture.h"

#include "ResourceManager.h"

Background::Background() : m_pTex(nullptr)
{
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::Render(HDC _hdc)
{
    Vec2 vPos = GetPos();
    Vec2 vSize = GetSize();
    int width = m_pTex->GetWidth();
    int height = m_pTex->GetHeight();

    HDC hTexDC = m_pTex->GetTexDC();

    StretchBlt(
        _hdc,
        (int)(vPos.x - vSize.x / 2),
        (int)(vPos.y - vSize.y / 2),
        (int)vSize.x, (int)vSize.y,
        hTexDC,
        0, 0,
        width, height,
        SRCCOPY
    );
}

