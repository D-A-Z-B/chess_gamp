#include "pch.h"
#include "Portal.h"

#include "Animator.h"
#include "Collider.h"

#include "ResourceManager.h";

Portal::Portal()
{
	AddComponent<Animator>();
	AddComponent<Collider>();

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Portal", L"Texture\\Portal\\Portal.bmp");
	GetComponent<Animator>()->CreateAnimation(L"Play", m_pTex, Vec2(0.f, 0.f), Vec2(185, 128), Vec2(185.f, 0.f), 3, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"Play", true);

	GetComponent<Collider>()->SetOwner(this);
}

Portal::~Portal()
{
}

void Portal::Init()
{
	Vec2 vSize = GetSize();
	Vec2 vPos = GetPos();
	GetComponent<Collider>()->SetSize(vSize);
	GetComponent<Collider>()->SetOffSetPos(vPos);
}

void Portal::Update()
{

}

void Portal::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Portal::EnterCollision(Collider* _other)
{
	cout << "ddd" << endl;
}

void Portal::StayCollision(Collider* _other)
{
}

void Portal::ExitCollision(Collider* _other)
{
}
