#pragma once
#include "ResourceBase.h"
class Texture : public ResourceBase
{
public:
    Texture();
    virtual ~Texture();
public:
	void Load(const wstring& _path);
	const LONG& GetWidth() const { return m_bitInfo.bmWidth; }
	const LONG& GetHeight()const { return m_bitInfo.bmHeight; }
	const HDC& GetTexDC()const { return m_hDC; }
private:
	HDC  m_hDC;
	HDC m_memDC;
	HBITMAP m_hBit;
	BITMAP m_bitInfo;

	long maxX;
	long maxY;
	long minX;
	long minY;
};

