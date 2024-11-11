#include "pch.h"
#include "Boss.h"

Boss::Boss() : m_hp(100), m_pTex(nullptr)
{
	StateMachine = new BossStateMachine();
}

Boss::~Boss()
{
	delete StateMachine;
}

void Boss::Update()
{
	StateMachine->CurrentState->UpdateState();
}

void Boss::Render(HDC _hdc)
{
}

void Boss::EnterCollision(Collider* _other)
{
}

void Boss::StayCollision(Collider* _other)
{
}

void Boss::ExitCollision(Collider* _other)
{
}
