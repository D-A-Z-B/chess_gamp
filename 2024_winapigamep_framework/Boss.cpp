#include "pch.h"
#include "Boss.h"

#include "PawnState.h"
#include "BishopState.h"
#include "KnightState.h"
#include "RookState.h"
#include "QueenState.h"
#include "KingState.h"

Boss::Boss() : m_hp(100), m_pTex(nullptr)
{
	StateMachine = new BossStateMachine();

	StateMachine->AddState(BOSS_STATE::Pawn, new PawnState(this, StateMachine, L"Pawn"));

	StateMachine->Initialize(BOSS_STATE::Pawn, this);
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
