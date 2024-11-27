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
	if (isAttack) {
		AttackRoutine();
	}
}

void KingAttackObject::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	Utils::RenderRectColor(_hdc, vPos, vSize.x, vSize.y, RGB(255, 0, 0));
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

void KingAttackObject::StartAttackRoutine(Vec2 size, float duration)
{
}

void KingAttackObject::AttackRoutine()
{
}
