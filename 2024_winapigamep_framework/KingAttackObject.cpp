#include "pch.h"
#include "KingAttackObject.h"

#include "EventManager.h"
#include "TimeManager.h"

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
	isAttack = true;
	targetSize = size;
	targerDuration = duration;
}

void KingAttackObject::AttackRoutine()
{
	static float elapsedTime = 0;

	Vec2 startSize = {0, 0};
	Vec2 targetSize = this->targetSize;

	if (elapsedTime < targerDuration) {
		float t = elapsedTime / targerDuration;
		float calcT = t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;

		float x = startSize.x * (1 - calcT) + targetSize.x * calcT;
		float y = startSize.y * (1 - calcT) + targetSize.y * calcT;

		SetSize({ x, y });

		cout << x << endl;

		elapsedTime += fDT;
	}
	else {
		GET_SINGLE(EventManager)->DeleteObject(this);

		elapsedTime = 0;
	}
}
