#include "pch.h"
#include "Boss.h"

#include "PawnState.h"
#include "BishopState.h"
#include "KnightState.h"
#include "RookState.h"
#include "QueenState.h"
#include "KingState.h"

#include "Texture.h"
#include "Collider.h"

#include "InputManager.h"
#include "SceneManager.h";
#include "EventManager.h";

#include "StateMachine.h"

Boss::Boss() : m_hp(100), m_pTex(nullptr)
{

}

Boss::~Boss()
{
	delete stateMachine;
}

void Boss::Initialize()
{
	ComponentInitialize();

	stateMachine = new StateMachine<BOSS_STATE>();

	stateMachine->AddState(BOSS_STATE::PAWN, new PawnState(this, stateMachine, L"B_Pawn"));
	stateMachine->AddState(BOSS_STATE::BISHOP, new BishopState(this, stateMachine, L"B_Bishop"));
	stateMachine->AddState(BOSS_STATE::ROOK, new RookState(this, stateMachine, L"B_Rook"));
	stateMachine->AddState(BOSS_STATE::KNIGHT, new KnightState(this, stateMachine, L"B_Knight"));
	stateMachine->AddState(BOSS_STATE::QUEEN, new QueenState(this, stateMachine, L"B_Queen"));
	stateMachine->AddState(BOSS_STATE::KING, new KingState(this, stateMachine, L"B_King"));

	stateMachine->Initialize(BOSS_STATE::PAWN, this);
}


void Boss::ComponentInitialize()
{
	Vec2 vSize = GetSize();

	AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
}

void Boss::Update()
{
	stateMachine->CurrentState->UpdateState();
}

void Boss::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(vPos.x - vSize.x / 2)
		, (int)(vPos.y - vSize.y / 2)
		, vSize.x, vSize.y,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	ComponentRender(_hdc);
}

void Boss::EnterCollision(Collider* _other)
{
	if (GetCurrentStateEnum() == BOSS_STATE::PAWN) return;
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->SetDead();
		//GET_SINGLE(EventManager)->ChangeScene(L"EndingScene");
	}
}

void Boss::StayCollision(Collider* _other)
{
}

void Boss::ExitCollision(Collider* _other)
{
}
