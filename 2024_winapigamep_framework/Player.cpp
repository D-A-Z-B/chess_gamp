#include "pch.h"
#include "Player.h"
#include "Aim.h"
#include "Projectile.h"

#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerDashState.h"
#include "PlayerDeadState.h"

#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "PlayerHealth.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

#include "Scene.h"
#include "StateMachine.h"

Player::Player()
	: m_pTex(nullptr), hp(5)
{
	//texure
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerMove", L"Texture\\Player\\Player.bmp");
	m_pDeadTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerDead", L"Texture\\Player\\Player_Dead.bmp");
	m_pFireTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerFire", L"Texture\\Player\\Player_Fire.bmp");

	//component
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"LPlayerMove", m_pTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerMove", m_pTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"LPlayerIdle", m_pTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerIdle", m_pTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->CreateAnimation(L"LPlayerIdleFire", m_pFireTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerIdleFire", m_pFireTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.f);
	GetComponent<Animator>()->CreateAnimation(L"LPlayerMoveFire", m_pFireTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerMoveFire", m_pFireTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"LPlayerDead", m_pDeadTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 9, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"RPlayerDead", m_pDeadTex, Vec2(0.f, 128.f), Vec2(128.f, 128.f), Vec2(128.f, 0.f), 9, 0.1f);

	AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
	GetComponent<Collider>()->SetSize({ 40.f, 40.f });

	//state
	stateMachine = new StateMachine<PLAYER_STATE>();

	stateMachine->AddState(PLAYER_STATE::IDLE, new PlayerIdleState(this, stateMachine, L"PlayerIdle"));
	stateMachine->AddState(PLAYER_STATE::MOVE, new PlayerMoveState(this, stateMachine, L"PlayerMove"));
	stateMachine->AddState(PLAYER_STATE::JUMP, new PlayerJumpState(this, stateMachine, L"PlayerIdle"));
	stateMachine->AddState(PLAYER_STATE::DASH, new PlayerDashState(this, stateMachine, L"PlayerIdle"));
	stateMachine->AddState(PLAYER_STATE::DEAD, new PlayerDeadState(this, stateMachine, L"PlayerDead"));

	stateMachine->Initialize(PLAYER_STATE::IDLE, this);

	//aim
	Object* pAim = new Aim;
	pAim->SetSize({ 50, 50 });
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pAim, LAYER::UI);

	//set
	GET_SINGLE(PlayerManager)->SetPlayer(this);
	SetName(L"Player");

	PlayerHealth* playerHealth = new PlayerHealth();
	playerHealth->SetName(L"PlayerHealth");
	playerHealth->SetSize({100, 10});
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(playerHealth, LAYER::UI);
}

Player::~Player()
{
	delete stateMachine;
}

void Player::Update()
{
	stateMachine->CurrentState->UpdateState();
	
	if (GetPos().y < GROUND && !isDash)
	{
		yVelocity += gravity * 200.f * fDT;
	}
	if (!isDash)
	{
		dashCoolTimer += fDT;
	}

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON) && !isDead)
	{
		if (!isShooting)
		{
			isShooting = true;
			ChangeAnimation(curAnimaton, true);
		}

		fireAnimTimer = 0;
		//GET_SINGLE(ResourceManager)->Play(L"PlayerShootSound", SOUND_CHANNEL::PLAYER);

		CreateProjectile();
	}
	if (isShooting)
	{
		fireAnimTimer += fDT;
		if (fireAnimTimer >= fireAnimTime)
		{
			fireAnimTimer = 0;
			isShooting = false;
			ChangeAnimation(curAnimaton, true);
		}
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
	if (currentStateEnum != PLAYER_STATE::DASH && !isDead)
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
	ComponentRender(_hdc);
}

void Player::ChangePacing(int pacing)
{
	if (pacing != isPacing)
	{
		isPacing = pacing;

		ChangeAnimation(curAnimaton, true);
	}
}

void Player::ChangeAnimation(wstring changeAnimation, bool isRepeat)
{
	curAnimaton = changeAnimation;

	//std::wcout << changeAnimation;
	GetComponent<Animator>()->StopAnimation();
	if (isShooting)
	{
		//std::cout << "Fire";
		GetComponent<Animator>()
			->PlayAnimation((isPacing == 1 ? L"R" : L"L") + changeAnimation + L"Fire", isRepeat, true);
	}
	else
	{
		GetComponent<Animator>()->PlayAnimation((isPacing == 1 ? L"R" : L"L") + changeAnimation, isRepeat);
	}
	//std::cout << "\n";
}

void Player::SetDead()
{
	isDead = true;
	isShooting = false;
}

void Player::ApplyDamage()
{
	hp--;
	if (hp <= 0) {
		SetDead();
		stateMachine->ChangeState(PLAYER_STATE::DEAD);
	}
}

void Player::CreateProjectile()
{
	Projectile* pProj = new Projectile;
	Vec2 vPos = GetPos();
	vPos.x += (GetSize().x / 2.f - 10) * isPacing;
	pProj->SetPos(vPos);
	pProj->SetSize({ 30.f,30.f });

	Vec2 dir = (Vec2)GET_MOUSEPOS - vPos;
	dir.Normalize();
	pProj->SetDir(dir);
	pProj->SetName(L"PlayerBullet");

	Vec2 v = { 0, -1 };
	float radian = acos(v.Dot(dir));
	float r = asin(v.Cross(dir));
	radian *= (r > 0 ? 1 : -1);
	pProj->SetAngle(radian);

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}
