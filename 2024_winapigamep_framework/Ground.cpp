#include "pch.h"
#include "Ground.h"
#include "Collider.h"
Ground::Ground()
{
	
}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Utils::RenderRectColor(_hdc, vPos, vSize.x, vSize.y, RGB(0, 0, 0));
}
