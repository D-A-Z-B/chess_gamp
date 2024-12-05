#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "Boss.h"
Projectile::Projectile()
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Boss\\W_Pawn.bmp");

	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f,20.f });
}

Projectile::~Projectile()
{
	DeleteDC(m_memDC);
}

void Projectile::Update()
{
	Vec2 vPos = GetPos();
	// 삼각함수의 단위가 2가지가 있다.
	// 라디안, 디그리
	//vPos.x += cosf(m_angle) * 500.f * fDT;
	//vPos.y += sinf(m_angle) * 500.f * fDT;

	vPos.x += m_vDir.x * m_speed * fDT;
	vPos.y += m_vDir.y * m_speed * fDT;
	SetPos(vPos);
	Vec2 vSize = GetSize();

	RECT clientRect;
	GetClientRect(GetActiveWindow(), &clientRect);

	if (vPos.x + vSize.x / 2 < clientRect.left ||
		vPos.x - vSize.x / 2 > clientRect.right ||
		vPos.y + vSize.y / 2 < clientRect.top ||
		vPos.y - vSize.y / 2 > clientRect.bottom)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	::TransparentBlt(_hdc
		, (int)(vPos.x - m_pTex->GetWidth() / 2)
		, (int)(vPos.y - m_pTex->GetHeight() / 2)
		, m_pTex->GetWidth()
		, m_pTex->GetHeight()
		, m_memDC
		, minX, minY
		, maxX - minX
		, maxY - minY
		, RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void Projectile::SetAngle(float _f)
{
	m_angle = _f;
	Rotate(m_angle);
}

void Projectile::Rotate(float angle)
{
	POINT vertices[4];
	double cosA = cos(angle);
	double sinA = sin(angle);

	int halfWidth = m_pTex->GetWidth() / 2;
	int halfHeight = m_pTex->GetHeight() / 2;

	vertices[0] = { (LONG)(-halfWidth * cosA + (-halfHeight) * sinA), (LONG)(-halfWidth * sinA - (-halfHeight) * cosA) };
	vertices[1] = { (LONG)(halfWidth * cosA + (-halfHeight) * sinA), (LONG)(halfWidth * sinA - (-halfHeight) * cosA) };
	vertices[2] = { (LONG)(-halfWidth * cosA + (halfHeight)*sinA), (LONG)(-halfWidth * sinA - (halfHeight)*cosA) };
	vertices[3] = { (LONG)(halfWidth * cosA + (halfHeight)*sinA), (LONG)(halfWidth * sinA - (halfHeight)*cosA) };

	minX = vertices[0].x, maxX = vertices[0].x;
	minY = vertices[0].y, maxY = vertices[0].y;
	for (int i = 0; i < 4; i++)
	{
		if (vertices[i].x > maxX) maxX = vertices[i].x;
		if (vertices[i].y > maxY) maxY = vertices[i].y;
		if (vertices[i].x < minX) minX = vertices[i].x;
		if (vertices[i].y < minY) minY = vertices[i].y;
	}

	m_memDC = CreateCompatibleDC(m_pTex->GetTexDC());
	HBITMAP hBmap = CreateCompatibleBitmap(m_pTex->GetTexDC(), maxX - minX, maxY - minY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_memDC, hBmap);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	RECT rect = { 0, 0, maxX - minX, maxY - minY };
	FillRect(m_memDC, &rect, hBrush);
	DeleteObject(hBrush);

	POINT verticesSubset[3] = { vertices[0], vertices[1], vertices[2] };
	for (int i = 0; i < 4; ++i) {
		if (minX < 0)
		{
			vertices[i].x -= minX;
			if (vertices[i].x > maxX)
			{
				maxX = vertices[i].x;
			}
		}
		if (minY < 0)
		{
			vertices[i].y -= minY;
			if (vertices[i].y > maxY)
			{
				maxY = vertices[i].y;
			}
		}


		if (i != 3)
		{
			verticesSubset[i] = vertices[i];
		}
	}

	if (minX < 0)
		minX = 0;
	if (minY < 0)
		minY = 0;

	PlgBlt(
		m_memDC, // 중간 저장 Device Conetext
		verticesSubset, // 좌상단, 우상단, 좌하단의 값만 매개변수로 전달
		m_pTex->GetTexDC(), // 원본 Device Context
		0, 0,
		m_pTex->GetWidth(), //  원본 비트맵 W
		m_pTex->GetHeight(), // 원본 비트맵 H
		NULL, 0, 0
	);
}

void Projectile::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Boss")
	{
		dynamic_cast<Boss*>(pOtherObj)->ApplyDamage();
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::StayCollision(Collider* _other)
{
}

void Projectile::ExitCollision(Collider* _other)
{
}