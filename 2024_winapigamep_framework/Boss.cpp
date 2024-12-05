#include "pch.h"
#include "Boss.h"
#include "Player.h"

#include "PawnState.h"
#include "BishopState.h"
#include "KnightState.h"
#include "RookState.h"
#include "QueenState.h"
#include "KingState.h"

#include "Texture.h"
#include "Collider.h"
#include "Scene.h"

#include "Effect.h"

#include "InputManager.h"
#include "SceneManager.h";
#include "EventManager.h";
#include "CameraManager.h"

#include "StateMachine.h"

Boss::Boss() : m_hp(500), m_pTex(nullptr)
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
	Object* pOtherObj = _other->GetOwner();

	if (pOtherObj->GetName() == L"PlayerBullet") {
		GET_SINGLE(ResourceManager)->Play(L"Boss_Hurt", SOUND_CHANNEL::EFFECT);
	}

	if (GetCurrentStateEnum() == BOSS_STATE::PAWN) return;

	if (pOtherObj->GetName() != L"PlayerBullet" && (GetCurrentStateEnum() == BOSS_STATE::BISHOP || GetCurrentStateEnum() == BOSS_STATE::ROOK)) {
		GET_SINGLE(CameraManager)->Shake(50, 0.15f);
	}

	if (pOtherObj->GetName() == L"Player")
	{
		Player* player = dynamic_cast<Player*>(pOtherObj);
		(*player).stateMachine->ChangeState(PLAYER_STATE::DEAD);
	}
}

void Boss::StayCollision(Collider* _other)
{
}

void Boss::ExitCollision(Collider* _other)
{
}

void Boss::ApplyDamage()
{
	m_hp--;
	if (m_hp <= 0) {
		Effect* eff = new Effect(EFFECT_TYPE::BOSS_DEAD, 0.001f, false);
		Vec2 vPos = GetPos();
		eff->SetPos(vPos);
		eff->SetSize({ 500, 500 });
		GET_SINGLE(ResourceManager)->Play(L"BossDead", SOUND_CHANNEL::BOSS);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(eff, LAYER::EFFECT);
		GET_SINGLE(CameraManager)->Shake(50, 0.1f);
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
	cout << "Current Hp: " + std::to_string(m_hp) << endl;
}
