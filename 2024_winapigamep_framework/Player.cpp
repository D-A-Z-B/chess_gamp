#include "pch.h"
#include "Player.h"
#include "Aim.h"
#include "Projectile.h"

#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerDashState.h"

#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "StateMachine.h"

Player::Player()
	: m_pTex(nullptr)
{
	//texure
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Player\\Player.bmp");

	//state
	stateMachine = new StateMachine<PLAYER_STATE>();

	stateMachine->AddState(PLAYER_STATE::IDLE, new PlayerIdleState(this, stateMachine));
	stateMachine->AddState(PLAYER_STATE::MOVE, new PlayerMoveState(this, stateMachine));
	stateMachine->AddState(PLAYER_STATE::JUMP, new PlayerJumpState(this, stateMachine));
	stateMachine->AddState(PLAYER_STATE::DASH, new PlayerDashState(this, stateMachine));

	stateMachine->Initialize(PLAYER_STATE::IDLE, this);


	//component
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"LPlayerMove", m_pTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerMove", m_pTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"LPlayerIdle", m_pTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerIdle", m_pTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->PlayAnimation(L"RPlayerIdle", true);

	AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
	GetComponent<Collider>()->SetSize({ 40.f, 40.f });

	//aim
	Object* pAim = new Aim;
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pAim, LAYER::AIM);

	//set
	GET_SINGLE(PlayerManager)->SetPlayer(this);
	SetName(L"Player");
}

Player::~Player()
{
	delete stateMachine;
}

void Player::Update()
{
	stateMachine->CurrentState->UpdateState();

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		CreateProjectile();
	}

	if (GetPos().y < GROUND && !isDash)
	{
		yVelocity += gravity * 200.f * fDT;
	}
	if (!isDash)
	{
		dashCoolTimer += fDT;
	}

	Vec2 vPos = GetPos();
	vPos.y += yVelocity * fDT;
	if (vPos.y >= GROUND)
	{
		yVelocity = 0;
		vPos.y = GROUND;
	}
	SetPos(vPos);

	CheckChangeState();
}

void Player::CheckChangeState()
{
	if (currentStateEnum != PLAYER_STATE::DASH)
	{
		if (GET_KEYDOWN(KEY_TYPE::LSHIFT) && dashCoolTimer >= dashCoolTime)
		{
			stateMachine->ChangeState(PLAYER_STATE::DASH);

			dashCoolTimer = 0;
			return;
		}

		if (currentStateEnum != PLAYER_STATE::JUMP && GET_KEYDOWN(KEY_TYPE::SPACE) && GetPos().y >= GROUND)
		{
			stateMachine->ChangeState(PLAYER_STATE::JUMP);
			return;
		}

		if (currentStateEnum == PLAYER_STATE::IDLE && (GET_KEY(KEY_TYPE::D) || GET_KEY(KEY_TYPE::A)))
		{
			stateMachine->ChangeState(PLAYER_STATE::MOVE);
			return;
		}
	}
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();



	ComponentRender(_hdc);
}

void Player::ChangePacing(int pacing)
{
	if (pacing != isPacing)
	{
		isPacing = pacing;

		ChangeAnimation();
	}
}

void Player::ChangeAnimation()
{
	if (isMove)
		GetComponent<Animator>()->PlayAnimation((isPacing == 1 ? L"RPlayerMove" : L"LPlayerMove"), true);
	else
		GetComponent<Animator>()->PlayAnimation((isPacing == 1 ? L"RPlayerIdle" : L"LPlayerIdle"), true);
}

void Player::CreateProjectile()
{
	Projectile* pProj = new Projectile;
	Vec2 vPos = GetPos();
	vPos.y -= GetSize().y / 2.f;
	pProj->SetPos(vPos);
	pProj->SetSize({ 30.f,30.f });

	Vec2 dir = (Vec2)GET_MOUSEPOS - vPos;
	dir.Normalize();
	pProj->SetDir(dir);
	pProj->SetName(L"PlayerBullet");

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}
