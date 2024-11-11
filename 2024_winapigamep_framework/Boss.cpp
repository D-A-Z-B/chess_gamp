#include "pch.h"
#include "Boss.h"

#include "PawnState.h"
#include "BishopState.h"
#include "KnightState.h"
#include "RookState.h"
#include "QueenState.h"
#include "KingState.h"

#include "InputManager.h"

Boss::Boss() : m_hp(100), m_pTex(nullptr)
{
	StateMachine = new BossStateMachine();

	StateMachine->AddState(BOSS_STATE::PAWN, new PawnState(this, StateMachine, L"Pawn"));
	StateMachine->AddState(BOSS_STATE::BISHOP, new BishopState(this, StateMachine, L"Bishop"));
	StateMachine->AddState(BOSS_STATE::ROOK, new RookState(this, StateMachine, L"Rook"));
	StateMachine->AddState(BOSS_STATE::KNIGHT, new KnightState(this, StateMachine, L"Knight"));
	StateMachine->AddState(BOSS_STATE::QUEEN, new QueenState(this, StateMachine, L"Queen"));
	StateMachine->AddState(BOSS_STATE::KING, new KingState(this, StateMachine, L"King"));

	StateMachine->Initialize(BOSS_STATE::PAWN, this);
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
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y, vSize.x, vSize.y);
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
