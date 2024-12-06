#include "pch.h"
#include "Portal.h"

#include "Animator.h"
#include "Collider.h"
#include "Scene.h"

#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h";

Portal::Portal()
{
	AddComponent<Animator>();

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Portal", L"Texture\\Portal\\Portal.bmp");
	GetComponent<Animator>()->CreateAnimation(L"Play", m_pTex, Vec2(0.f, 0.f), Vec2(185, 128), Vec2(185.f, 0.f), 3, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"Play", true);
}

Portal::~Portal()
{
}

void Portal::Init()
{
	Vec2 vSize = GetSize();
	Vec2 vPos = GetPos();
	AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
	GetComponent<Collider>()->SetSize({ vSize.x / 2, vSize.y});
}

void Portal::Update()
{
	if (isClear) {
		ClearRoutine();
	}
}

void Portal::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Portal::ClearRoutine()
{
	static float elapsedTime = 0;
	float time = 3.5f;

	static bool isExecutedFadeIn = false;

	if (isExecutedFadeIn == false) {
		GET_SINGLE(SceneManager)->GetCurrentScene()->StartSceneBlending(time - 0.5f, 255, true, WHITENESS);
		isExecutedFadeIn = true;
	}

	if (elapsedTime < time) {
		float t = elapsedTime / time;

		GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, t);

		elapsedTime += fDT;
	}
	else {
		elapsedTime = 0;
		isExecutedFadeIn = false;
		isClear = false;

	}
}

void Portal::EnterCollision(Collider* _other)
{

}

void Portal::StayCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		if (GET_KEYDOWN(KEY_TYPE::W)) {
			isClear = true;
		}
	}
}

void Portal::ExitCollision(Collider* _other)
{

}
