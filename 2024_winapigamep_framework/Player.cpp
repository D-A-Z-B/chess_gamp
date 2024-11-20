#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Aim.h"

#define ISGROUND (vPos.y >= 550)

Player::Player()
	: m_pTex(nullptr)
{
	Object* pAim = new Aim;
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pAim, LAYER::AIM);

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");

	AddComponent<Animator>();
	GetComponent<Animator>()
		->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()
		->PlayAnimation(L"JiwooFront", true);

	AddComponent<Collider>();
	GetComponent<Collider>()
		->SetSize({ 40.f, 40.f });

	GET_SINGLE(PlayerManager)->SetPlayer(this);

}
Player::~Player()
{
}
void Player::Update()
{
	Vec2 vPos = GetPos();

	if (GET_KEY(KEY_TYPE::A))
	{
		vPos.x -= 200.f * fDT;
		m_ispacing = -1;
	}
	if (GET_KEY(KEY_TYPE::D))
	{
		vPos.x += 200.f * fDT;
		m_ispacing = 1;
	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE) && (ISGROUND || m_jumpCnt <= 1))
	{
		m_speed.y = -m_jumpPower;
		m_jumpCnt++;
	}
	if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
	{
		m_isDash = true;
		m_speed.x = m_dashPower * m_ispacing;
	}
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
		CreateProjectile();

	if (m_isDash)
	{
		m_dashTimer += fDT;
		if (m_dashTimer > 0.05f)
		{
			m_dashTimer = 0;
			m_isDash = false;
			m_speed.x = 0;
		}
	}

	if (!ISGROUND)
		m_speed.y += m_gravity * fDT;

	vPos += m_speed;
	if (ISGROUND)
	{
		vPos.y = 550;
		m_speed.y = 0;
		m_jumpCnt = 0;
	}
	SetPos(vPos);
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	ComponentRender(_hdc);
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