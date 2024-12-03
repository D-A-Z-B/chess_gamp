#include "pch.h"
#include "Texture.h"
#include <assert.h>
#include "Core.h"
Texture::Texture()
	: m_hDC(nullptr)
	, m_hBit(nullptr)
	, m_bitInfo{}
{
}

Texture::~Texture()
{
	::DeleteDC(m_hDC);
	::DeleteDC(m_memDC);
	::DeleteObject(m_hBit);
}

void Texture::Load(const wstring& _path)
{
	// 1: 인스턴스 핸들(nullptr: 독립형 리소스)
	// 2: 경로
	// 3. BITMAP / ICON / CURSOR / .. 
	// 4,5 : 이미지(리소스) 크기
	// 6: 추가 플래그
	m_hBit = (HBITMAP)::LoadImage(nullptr, _path.c_str(), IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit); // nullptr이면 assert가 걸립니다.
	m_hDC = ::CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
	::SelectObject(m_hDC, m_hBit);
	::GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	int a = 0;
}

void Texture::Render(HDC _mainDC, Vec2 _vPos)
{
	::TransparentBlt(_mainDC
		, (int)(_vPos.x - m_bitInfo.bmWidth / 2)
		, (int)(_vPos.y - m_bitInfo.bmHeight / 2)
		, m_bitInfo.bmWidth
		, m_bitInfo.bmHeight
		, m_memDC
		, minX, minY
		, maxX - minX
		, maxY - minY
		, RGB(255, 0, 255));
}

void Texture::Rotate(float angle)
{
	POINT vertices[4];
	double cosA = cos(angle);
	double sinA = sin(angle);

	int halfWidth = m_bitInfo.bmWidth / 2;
	int halfHeight = m_bitInfo.bmHeight / 2;

	vertices[0] = { (LONG)(-halfWidth * cosA + (-halfHeight) * sinA), (LONG)(-halfWidth * sinA - (-halfHeight) * cosA) };
	vertices[1] = { (LONG)(halfWidth * cosA + (-halfHeight) * sinA), (LONG)(halfWidth * sinA - (-halfHeight) * cosA) };
	vertices[2] = { (LONG)(-halfWidth * cosA + (halfHeight) * sinA), (LONG)(-halfWidth * sinA - (halfHeight) * cosA) };
	vertices[3] = { (LONG)(halfWidth * cosA + (halfHeight) * sinA), (LONG)(halfWidth * sinA - (halfHeight) * cosA) };

	minX = vertices[0].x, maxX = vertices[0].x;
	minY = vertices[0].y, maxY = vertices[0].y;
	for (int i = 0; i < 4; i++)
	{
		if (vertices[i].x > maxX) maxX = vertices[i].x;
		if (vertices[i].y > maxY) maxY = vertices[i].y;
		if (vertices[i].x < minX) minX = vertices[i].x;
		if (vertices[i].y < minY) minY = vertices[i].y;
	}

	m_memDC = CreateCompatibleDC(m_hDC);
	HBITMAP hBmap = CreateCompatibleBitmap(m_hDC, maxX - minX, maxY - minY);
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
		m_hDC, // 원본 Device Context
		0, 0,
		m_bitInfo.bmWidth, //  원본 비트맵 W
		m_bitInfo.bmHeight, // 원본 비트맵 H
		NULL, 0, 0
	);
}
