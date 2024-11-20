#include "pch.h"
#include "Aim.h"
#include "InputManager.h"

Aim::Aim()
{
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
	Utils::RenderCircleColor(_hdc, GetPos(), 5, RGB(255, 0, 0));
}
