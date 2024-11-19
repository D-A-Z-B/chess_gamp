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

#include "PlayerManager.h"

#define ISGROUND (vPos.y >= 550)

Player::Player()
	: m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");

	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);

	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 40.f, 40.f });

	GET_SINGLE(PlayerManager)->SetPlayer(this);

}
Player::~Player()
{
}
void Player::Update()
{
	Vec2 vPos = GetPos();
	if (GET_KEY(KEY_TYPE::A))
		vPos.x -= 200.f * fDT;
	if (GET_KEY(KEY_TYPE::D))
		vPos.x += 200.f * fDT;
	if (GET_KEYDOWN(KEY_TYPE::SPACE) && (ISGROUND || m_jumpCnt <= m_maxJumpCnt - 1))
	{
		m_speed = -m_jumpPower;
		m_jumpCnt++;
	}
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		CreateProjectile();
	}

	vPos += {0.f, m_speed};
	if (!ISGROUND)
		m_speed += m_gravity * fDT;

	if (ISGROUND)
	{
		vPos.y = 550;
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
	dir = NORMALIZE(dir);
	pProj->SetDir(dir);
	pProj->SetName(L"PlayerBullet");

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}