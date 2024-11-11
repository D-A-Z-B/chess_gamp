#include "pch.h"
#include "Boss.h"

Boss::Boss() : m_hp(100)
{
	StateMachine = new BossStateMachine();
}

Boss::~Boss()
{
	delete StateMachine;
}

void Boss::Update()
{
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
