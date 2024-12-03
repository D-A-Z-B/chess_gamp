#include "pch.h"
#include "QueenProjectile.h"
#include "Player.h"

#include "TimeManager.h"
#include "EventManager.h"

#include "Collider.h"
#include "Texture.h"

QueenProjectile::QueenProjectile()
{
	this->AddComponent<Collider>();

	Vec2 vSize = GetSize();
}

QueenProjectile::~QueenProjectile()
{
}

void QueenProjectile::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += m_vDir.x * speed * fDT;
	vPos.y += m_vDir.y * speed * fDT;
	SetPos(vPos);
	RECT clientRect;
	GetClientRect(GetActiveWindow(), &clientRect);

	Vec2 vSize = GetSize();
	if (vPos.x + vSize.x / 2 < clientRect.left ||
		vPos.x - vSize.x / 2 > clientRect.right ||
		vPos.y + vSize.y / 2 < clientRect.top ||
		vPos.y - vSize.y / 2 > clientRect.bottom)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}

}

void QueenProjectile::Render(HDC _hdc)
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

void QueenProjectile::Shoot(Vec2 position, Vec2 dir)
{
	Vec2 vSize = GetSize();
	GetComponent<Collider>()->SetOffSetPos({ 0.f, 0.f });
	GetComponent<Collider>()->SetSize({ vSize.x / 3, vSize.y / 3});

	SetPos(position);
	m_vDir = dir;
}

void QueenProjectile::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		Player* player = dynamic_cast<Player*>(pOtherObj);
		(*player).stateMachine->ChangeState(PLAYER_STATE::DEAD);
	}
}

void QueenProjectile::StayCollision(Collider* _other)
{
}

void QueenProjectile::ExitCollision(Collider* _other)
{
}

