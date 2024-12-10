#include "pch.h"
#include "PlayerHealth.h"

#include "PlayerManager.h"

void PlayerHealth::Update()
{
	static int defaultXSize = GetSize().x;

	Vec2 playerPos = GET_SINGLE(PlayerManager)->GetPlayer()->GetPos();

	int currentHp = GET_SINGLE(PlayerManager)->GetPlayer()->GetCurrentHP();
	int defaultHp = GET_SINGLE(PlayerManager)->GetPlayer()->GetDefaultHP();

	Vec2 size = { defaultXSize - (defaultXSize / defaultHp) * (defaultHp - currentHp), 10};
	Vec2 pos = { playerPos.x - ((defaultXSize / defaultHp) * (defaultHp - currentHp) / 2), playerPos.y + 35.f };
	SetSize(size);
	SetPos(pos);
}

void PlayerHealth::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Utils::RenderRectColor(_hdc, vPos, vSize.x, vSize.y, RGB(255, 0, 0));
}
