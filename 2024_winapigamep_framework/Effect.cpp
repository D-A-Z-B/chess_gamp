#include "pch.h"
#include "Effect.h"

#include "Texture.h"
#include "Animator.h"

#include "TimeManager.h"
#include "EventManager.h"
#include "ResourceManager.h"

Effect::Effect(EFFECT_TYPE type, float time, bool isReapt) 
	: type(type)
	, time(time)
	, elapsedTime(0.f)
	, isReapt(isReapt)
	, pTex(nullptr)
{
	switch (type) {
		case EFFECT_TYPE::BOSS_DEAD: {
			pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BossDeadEffect", L"Texture\\Effect\\BossDeadEffect.bmp");
			break;
		}
		case EFFECT_TYPE::BOSS_HIT: {
			// 아직 없음
			break;
		}
		case EFFECT_TYPE::PLAYER_DEAD: {
			// 아직 없음
			break;
		}
	}

	if (pTex == nullptr) {
		return;
	}

	int width = pTex->GetWidth();
	int hight = pTex->GetHeight();
	int frame = width / hight;
	time *= frame;

	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"Play", pTex, Vec2(0, 0), Vec2(hight, hight), Vec2(hight, 0), frame, time);
	GetComponent<Animator>()->PlayAnimation(L"Play", isReapt);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	elapsedTime += fDT;
	if (elapsedTime >= 1) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Effect::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}
