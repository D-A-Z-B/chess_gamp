#include "pch.h"
#include "KingAttackObject.h"

#include "EventManager.h"
#include "TimeManager.h"
#include "CameraManager.h"

#include "Collider.h"

KingAttackObject::KingAttackObject()
{
	AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
}

KingAttackObject::~KingAttackObject()
{
}

void KingAttackObject::Update()
{
	Vec2 vSize = GetSize();

	GetComponent<Collider>()->SetOffSetPos({ 0.f, 0.f});
	GetComponent<Collider>()->SetSize({ vSize.x, vSize.y });

	if (isAttack) {
		AttackRoutine();
	}
	else if (isEnd) {
		EndRoutine();
	}
}

void KingAttackObject::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	Utils::RenderRectColor(_hdc, vPos, vSize.x, vSize.y, RGB(255, 0, 0));

	ComponentRender(_hdc);
}
void KingAttackObject::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->SetDead();
		//GET_SINGLE(EventManager)->ChangeScene(L"EndingScene");
	}
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

		elapsedTime += fDT;
	}
	else {
		isEnd = true;
		isAttack = false;
		elapsedTime = 0;
	}
}

void KingAttackObject::EndRoutine()
{
	static float elapsedTime = 0;

	Vec2 startSize = this->targetSize;
	Vec2 targetSize = { 0, 0 };

	if (elapsedTime < targerDuration) {
		float t = elapsedTime / targerDuration;
		float calcT = t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;

		float x = startSize.x * (1 - calcT) + targetSize.x * calcT;
		float y = startSize.y * (1 - calcT) + targetSize.y * calcT;

		SetSize({ x, y });

		elapsedTime += fDT;
	}
	else {
		isEnd = false;
		elapsedTime = 0;

		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}
