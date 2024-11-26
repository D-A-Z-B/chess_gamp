#include "pch.h"
#include "KingAttackObject.h"

KingAttackObject::KingAttackObject()
{
}

KingAttackObject::~KingAttackObject()
{
}

void KingAttackObject::Update()
{

}

void KingAttackObject::Render(HDC _hdc)
{
	static COLORREF color;

	if (canAttack) {
		color = RGB(0, 0, 0);
	}
	else {
		color = RGB(255, 0, 0);
	}

	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();


	Utils::RenderRectColor(_hdc, vPos, vSize.x, vSize.y, color);
}

void KingAttackObject::EnterCollision(Collider* _other)
{
}

void KingAttackObject::StayCollision(Collider* _other)
{
}

void KingAttackObject::ExitCollision(Collider* _other)
{
}
